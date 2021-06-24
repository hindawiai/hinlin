<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*****************************************************************************
 *
 * Copyright (C) 2008 Cedric Bregardis <cedric.bregardis@मुक्त.fr> and
 * Jean-Christian Hassler <jhassler@मुक्त.fr>
 *
 * This file is part of the Audiowerk2 ALSA driver
 *
 *****************************************************************************/

#घोषणा AW2_SAA7146_M

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "saa7146.h"
#समावेश "aw2-saa7146.h"

#समावेश "aw2-tsl.c"

#घोषणा WRITEREG(value, addr) ग_लिखोl((value), chip->base_addr + (addr))
#घोषणा READREG(addr) पढ़ोl(chip->base_addr + (addr))

अटल काष्ठा snd_aw2_saa7146_cb_param
 arr_substream_it_playback_cb[NB_STREAM_PLAYBACK];
अटल काष्ठा snd_aw2_saa7146_cb_param
 arr_substream_it_capture_cb[NB_STREAM_CAPTURE];

अटल पूर्णांक snd_aw2_saa7146_get_limit(पूर्णांक size);

/* chip-specअगरic deकाष्ठाor */
पूर्णांक snd_aw2_saa7146_मुक्त(काष्ठा snd_aw2_saa7146 *chip)
अणु
	/* disable all irqs */
	WRITEREG(0, IER);

	/* reset saa7146 */
	WRITEREG((MRST_N << 16), MC1);

	/* Unset base addr */
	chip->base_addr = शून्य;

	वापस 0;
पूर्ण

व्योम snd_aw2_saa7146_setup(काष्ठा snd_aw2_saa7146 *chip,
			   व्योम __iomem *pci_base_addr)
अणु
	/* set PCI burst/threshold

	   Burst length definition
	   VALUE    BURST LENGTH
	   000      1 Dword
	   001      2 Dwords
	   010      4 Dwords
	   011      8 Dwords
	   100      16 Dwords
	   101      32 Dwords
	   110      64 Dwords
	   111      128 Dwords

	   Threshold definition
	   VALUE    WRITE MODE              READ MODE
	   00       1 Dword of valid data   1 empty Dword
	   01       4 Dwords of valid data  4 empty Dwords
	   10       8 Dwords of valid data  8 empty Dwords
	   11       16 Dwords of valid data 16 empty Dwords */

	अचिन्हित पूर्णांक acon2;
	अचिन्हित पूर्णांक acon1 = 0;
	पूर्णांक i;

	/* Set base addr */
	chip->base_addr = pci_base_addr;

	/* disable all irqs */
	WRITEREG(0, IER);

	/* reset saa7146 */
	WRITEREG((MRST_N << 16), MC1);

	/* enable audio पूर्णांकerface */
#अगर_घोषित __BIG_ENDIAN
	acon1 |= A1_SWAP;
	acon1 |= A2_SWAP;
#पूर्ण_अगर
	/* WS0_CTRL, WS0_SYNC: input TSL1, I2S */

	/* At initialization WS1 and WS2 are disabled (configured as input) */
	acon1 |= 0 * WS1_CTRL;
	acon1 |= 0 * WS2_CTRL;

	/* WS4 is not used. So it must not restart A2.
	   This is why it is configured as output (क्रमce to low) */
	acon1 |= 3 * WS4_CTRL;

	/* WS3_CTRL, WS3_SYNC: output TSL2, I2S */
	acon1 |= 2 * WS3_CTRL;

	/* A1 and A2 are active and asynchronous */
	acon1 |= 3 * AUDIO_MODE;
	WRITEREG(acon1, ACON1);

	/* The following comes from original winकरोws driver.
	   It is needed to have a correct behavior of input and output
	   simultenously, but I करोn't know why ! */
	WRITEREG(3 * (BurstA1_in) + 3 * (ThreshA1_in) +
		 3 * (BurstA1_out) + 3 * (ThreshA1_out) +
		 3 * (BurstA2_out) + 3 * (ThreshA2_out), PCI_BT_A);

	/* enable audio port pins */
	WRITEREG((EAP << 16) | EAP, MC1);

	/* enable I2C */
	WRITEREG((EI2C << 16) | EI2C, MC1);
	/* enable पूर्णांकerrupts */
	WRITEREG(A1_out | A2_out | A1_in | IIC_S | IIC_E, IER);

	/* audio configuration */
	acon2 = A2_CLKSRC | BCLK1_OEN;
	WRITEREG(acon2, ACON2);

	/* By शेष use analog input */
	snd_aw2_saa7146_use_digital_input(chip, 0);

	/* TSL setup */
	क्रम (i = 0; i < 8; ++i) अणु
		WRITEREG(tsl1[i], TSL1 + (i * 4));
		WRITEREG(tsl2[i], TSL2 + (i * 4));
	पूर्ण

पूर्ण

व्योम snd_aw2_saa7146_pcm_init_playback(काष्ठा snd_aw2_saa7146 *chip,
				       पूर्णांक stream_number,
				       अचिन्हित दीर्घ dma_addr,
				       अचिन्हित दीर्घ period_size,
				       अचिन्हित दीर्घ buffer_size)
अणु
	अचिन्हित दीर्घ dw_page, dw_limit;

	/* Configure DMA क्रम substream
	   Configuration inक्रमmations: ALSA has allocated continuous memory
	   pages. So we करोn't need to use MMU of saa7146.
	 */

	/* No MMU -> nothing to करो with PageA1, we only configure the limit of
	   PageAx_out रेजिस्टर */
	/* Disable MMU */
	dw_page = (0L << 11);

	/* Configure Limit क्रम DMA access.
	   The limit रेजिस्टर defines an address limit, which generates
	   an पूर्णांकerrupt अगर passed by the actual PCI address poपूर्णांकer.
	   '0001' means an पूर्णांकerrupt will be generated अगर the lower
	   6 bits (64 bytes) of the PCI address are zero. '0010'
	   defines a limit of 128 bytes, '0011' one of 256 bytes, and
	   so on up to 1 Mbyte defined by '1111'. This पूर्णांकerrupt range
	   can be calculated as follows:
	   Range = 2^(5 + Limit) bytes.
	 */
	dw_limit = snd_aw2_saa7146_get_limit(period_size);
	dw_page |= (dw_limit << 4);

	अगर (stream_number == 0) अणु
		WRITEREG(dw_page, PageA2_out);

		/* Base address क्रम DMA transfert. */
		/* This address has been reserved by ALSA. */
		/* This is a physical address */
		WRITEREG(dma_addr, BaseA2_out);

		/* Define upper limit क्रम DMA access */
		WRITEREG(dma_addr + buffer_size, ProtA2_out);

	पूर्ण अन्यथा अगर (stream_number == 1) अणु
		WRITEREG(dw_page, PageA1_out);

		/* Base address क्रम DMA transfert. */
		/* This address has been reserved by ALSA. */
		/* This is a physical address */
		WRITEREG(dma_addr, BaseA1_out);

		/* Define upper limit क्रम DMA access */
		WRITEREG(dma_addr + buffer_size, ProtA1_out);
	पूर्ण अन्यथा अणु
		pr_err("aw2: snd_aw2_saa7146_pcm_init_playback: "
		       "Substream number is not 0 or 1 -> not managed\n");
	पूर्ण
पूर्ण

व्योम snd_aw2_saa7146_pcm_init_capture(काष्ठा snd_aw2_saa7146 *chip,
				      पूर्णांक stream_number, अचिन्हित दीर्घ dma_addr,
				      अचिन्हित दीर्घ period_size,
				      अचिन्हित दीर्घ buffer_size)
अणु
	अचिन्हित दीर्घ dw_page, dw_limit;

	/* Configure DMA क्रम substream
	   Configuration inक्रमmations: ALSA has allocated continuous memory
	   pages. So we करोn't need to use MMU of saa7146.
	 */

	/* No MMU -> nothing to करो with PageA1, we only configure the limit of
	   PageAx_out रेजिस्टर */
	/* Disable MMU */
	dw_page = (0L << 11);

	/* Configure Limit क्रम DMA access.
	   The limit रेजिस्टर defines an address limit, which generates
	   an पूर्णांकerrupt अगर passed by the actual PCI address poपूर्णांकer.
	   '0001' means an पूर्णांकerrupt will be generated अगर the lower
	   6 bits (64 bytes) of the PCI address are zero. '0010'
	   defines a limit of 128 bytes, '0011' one of 256 bytes, and
	   so on up to 1 Mbyte defined by '1111'. This पूर्णांकerrupt range
	   can be calculated as follows:
	   Range = 2^(5 + Limit) bytes.
	 */
	dw_limit = snd_aw2_saa7146_get_limit(period_size);
	dw_page |= (dw_limit << 4);

	अगर (stream_number == 0) अणु
		WRITEREG(dw_page, PageA1_in);

		/* Base address क्रम DMA transfert. */
		/* This address has been reserved by ALSA. */
		/* This is a physical address */
		WRITEREG(dma_addr, BaseA1_in);

		/* Define upper limit क्रम DMA access  */
		WRITEREG(dma_addr + buffer_size, ProtA1_in);
	पूर्ण अन्यथा अणु
		pr_err("aw2: snd_aw2_saa7146_pcm_init_capture: "
		       "Substream number is not 0 -> not managed\n");
	पूर्ण
पूर्ण

व्योम snd_aw2_saa7146_define_it_playback_callback(अचिन्हित पूर्णांक stream_number,
						 snd_aw2_saa7146_it_cb
						 p_it_callback,
						 व्योम *p_callback_param)
अणु
	अगर (stream_number < NB_STREAM_PLAYBACK) अणु
		arr_substream_it_playback_cb[stream_number].p_it_callback =
		    (snd_aw2_saa7146_it_cb) p_it_callback;
		arr_substream_it_playback_cb[stream_number].p_callback_param =
		    (व्योम *)p_callback_param;
	पूर्ण
पूर्ण

व्योम snd_aw2_saa7146_define_it_capture_callback(अचिन्हित पूर्णांक stream_number,
						snd_aw2_saa7146_it_cb
						p_it_callback,
						व्योम *p_callback_param)
अणु
	अगर (stream_number < NB_STREAM_CAPTURE) अणु
		arr_substream_it_capture_cb[stream_number].p_it_callback =
		    (snd_aw2_saa7146_it_cb) p_it_callback;
		arr_substream_it_capture_cb[stream_number].p_callback_param =
		    (व्योम *)p_callback_param;
	पूर्ण
पूर्ण

व्योम snd_aw2_saa7146_pcm_trigger_start_playback(काष्ठा snd_aw2_saa7146 *chip,
						पूर्णांक stream_number)
अणु
	अचिन्हित पूर्णांक acon1 = 0;
	/* In aw8 driver, dma transfert is always active. It is
	   started and stopped in a larger "space" */
	acon1 = READREG(ACON1);
	अगर (stream_number == 0) अणु
		WRITEREG((TR_E_A2_OUT << 16) | TR_E_A2_OUT, MC1);

		/* WS2_CTRL, WS2_SYNC: output TSL2, I2S */
		acon1 |= 2 * WS2_CTRL;
		WRITEREG(acon1, ACON1);

	पूर्ण अन्यथा अगर (stream_number == 1) अणु
		WRITEREG((TR_E_A1_OUT << 16) | TR_E_A1_OUT, MC1);

		/* WS1_CTRL, WS1_SYNC: output TSL1, I2S */
		acon1 |= 1 * WS1_CTRL;
		WRITEREG(acon1, ACON1);
	पूर्ण
पूर्ण

व्योम snd_aw2_saa7146_pcm_trigger_stop_playback(काष्ठा snd_aw2_saa7146 *chip,
					       पूर्णांक stream_number)
अणु
	अचिन्हित पूर्णांक acon1 = 0;
	acon1 = READREG(ACON1);
	अगर (stream_number == 0) अणु
		/* WS2_CTRL, WS2_SYNC: output TSL2, I2S */
		acon1 &= ~(3 * WS2_CTRL);
		WRITEREG(acon1, ACON1);

		WRITEREG((TR_E_A2_OUT << 16), MC1);
	पूर्ण अन्यथा अगर (stream_number == 1) अणु
		/* WS1_CTRL, WS1_SYNC: output TSL1, I2S */
		acon1 &= ~(3 * WS1_CTRL);
		WRITEREG(acon1, ACON1);

		WRITEREG((TR_E_A1_OUT << 16), MC1);
	पूर्ण
पूर्ण

व्योम snd_aw2_saa7146_pcm_trigger_start_capture(काष्ठा snd_aw2_saa7146 *chip,
					       पूर्णांक stream_number)
अणु
	/* In aw8 driver, dma transfert is always active. It is
	   started and stopped in a larger "space" */
	अगर (stream_number == 0)
		WRITEREG((TR_E_A1_IN << 16) | TR_E_A1_IN, MC1);
पूर्ण

व्योम snd_aw2_saa7146_pcm_trigger_stop_capture(काष्ठा snd_aw2_saa7146 *chip,
					      पूर्णांक stream_number)
अणु
	अगर (stream_number == 0)
		WRITEREG((TR_E_A1_IN << 16), MC1);
पूर्ण

irqवापस_t snd_aw2_saa7146_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक isr;
	__always_unused अचिन्हित पूर्णांक iicsta;
	काष्ठा snd_aw2_saa7146 *chip = dev_id;

	isr = READREG(ISR);
	अगर (!isr)
		वापस IRQ_NONE;

	WRITEREG(isr, ISR);

	अगर (isr & (IIC_S | IIC_E)) अणु
		iicsta = READREG(IICSTA);
		WRITEREG(0x100, IICSTA);
	पूर्ण

	अगर (isr & A1_out) अणु
		अगर (arr_substream_it_playback_cb[1].p_it_callback != शून्य) अणु
			arr_substream_it_playback_cb[1].
			    p_it_callback(arr_substream_it_playback_cb[1].
					  p_callback_param);
		पूर्ण
	पूर्ण
	अगर (isr & A2_out) अणु
		अगर (arr_substream_it_playback_cb[0].p_it_callback != शून्य) अणु
			arr_substream_it_playback_cb[0].
			    p_it_callback(arr_substream_it_playback_cb[0].
					  p_callback_param);
		पूर्ण

	पूर्ण
	अगर (isr & A1_in) अणु
		अगर (arr_substream_it_capture_cb[0].p_it_callback != शून्य) अणु
			arr_substream_it_capture_cb[0].
			    p_it_callback(arr_substream_it_capture_cb[0].
					  p_callback_param);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अचिन्हित पूर्णांक snd_aw2_saa7146_get_hw_ptr_playback(काष्ठा snd_aw2_saa7146 *chip,
						 पूर्णांक stream_number,
						 अचिन्हित अक्षर *start_addr,
						 अचिन्हित पूर्णांक buffer_size)
अणु
	दीर्घ pci_adp = 0;
	माप_प्रकार ptr = 0;

	अगर (stream_number == 0) अणु
		pci_adp = READREG(PCI_ADP3);
		ptr = pci_adp - (दीर्घ)start_addr;

		अगर (ptr == buffer_size)
			ptr = 0;
	पूर्ण
	अगर (stream_number == 1) अणु
		pci_adp = READREG(PCI_ADP1);
		ptr = pci_adp - (माप_प्रकार) start_addr;

		अगर (ptr == buffer_size)
			ptr = 0;
	पूर्ण
	वापस ptr;
पूर्ण

अचिन्हित पूर्णांक snd_aw2_saa7146_get_hw_ptr_capture(काष्ठा snd_aw2_saa7146 *chip,
						पूर्णांक stream_number,
						अचिन्हित अक्षर *start_addr,
						अचिन्हित पूर्णांक buffer_size)
अणु
	माप_प्रकार pci_adp = 0;
	माप_प्रकार ptr = 0;
	अगर (stream_number == 0) अणु
		pci_adp = READREG(PCI_ADP2);
		ptr = pci_adp - (माप_प्रकार) start_addr;

		अगर (ptr == buffer_size)
			ptr = 0;
	पूर्ण
	वापस ptr;
पूर्ण

व्योम snd_aw2_saa7146_use_digital_input(काष्ठा snd_aw2_saa7146 *chip,
				       पूर्णांक use_digital)
अणु
	/* FIXME: चयन between analog and digital input करोes not always work.
	   It can produce a kind of white noise. It seams that received data
	   are inverted someसमय (endian inversion). Why ? I करोn't know, maybe
	   a problem of synchronization... However क्रम the समय being I have
	   not found the problem. Workaround: चयन again (and again) between
	   digital and analog input until it works. */
	अगर (use_digital)
		WRITEREG(0x40, GPIO_CTRL);
	अन्यथा
		WRITEREG(0x50, GPIO_CTRL);
पूर्ण

पूर्णांक snd_aw2_saa7146_is_using_digital_input(काष्ठा snd_aw2_saa7146 *chip)
अणु
	अचिन्हित पूर्णांक reg_val = READREG(GPIO_CTRL);
	अगर ((reg_val & 0xFF) == 0x40)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण


अटल पूर्णांक snd_aw2_saa7146_get_limit(पूर्णांक size)
अणु
	पूर्णांक limitsize = 32;
	पूर्णांक limit = 0;
	जबतक (limitsize < size) अणु
		limitsize *= 2;
		limit++;
	पूर्ण
	वापस limit;
पूर्ण
