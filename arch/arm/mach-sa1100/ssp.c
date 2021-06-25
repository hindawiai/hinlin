<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-sa1100/ssp.c
 *
 *  Copyright (C) 2003 Russell King.
 *
 *  Generic SSP driver.  This provides the generic core क्रम simple
 *  IO-based SSP applications.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>
#समावेश <यंत्र/hardware/ssp.h>

#घोषणा TIMEOUT 100000

अटल irqवापस_t ssp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक status = Ser4SSSR;

	अगर (status & SSSR_ROR)
		prपूर्णांकk(KERN_WARNING "SSP: receiver overrun\n");

	Ser4SSSR = SSSR_ROR;

	वापस status ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/**
 * ssp_ग_लिखो_word - ग_लिखो a word to the SSP port
 * @data: 16-bit, MSB justअगरied data to ग_लिखो.
 *
 * Wait क्रम a मुक्त entry in the SSP transmit FIFO, and ग_लिखो a data
 * word to the SSP port.  Wait क्रम the SSP port to start sending
 * the data.
 *
 * The caller is expected to perक्रमm the necessary locking.
 *
 * Returns:
 *   %-ETIMEDOUT	समयout occurred
 *   0			success
 */
पूर्णांक ssp_ग_लिखो_word(u16 data)
अणु
	पूर्णांक समयout = TIMEOUT;

	जबतक (!(Ser4SSSR & SSSR_TNF)) अणु
	        अगर (!--समयout)
	        	वापस -ETIMEDOUT;
		cpu_relax();
	पूर्ण

	Ser4SSDR = data;

	समयout = TIMEOUT;
	जबतक (!(Ser4SSSR & SSSR_BSY)) अणु
	        अगर (!--समयout)
	        	वापस -ETIMEDOUT;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ssp_पढ़ो_word - पढ़ो a word from the SSP port
 *
 * Wait क्रम a data word in the SSP receive FIFO, and वापस the
 * received data.  Data is LSB justअगरied.
 *
 * Note: Currently, अगर data is not expected to be received, this
 * function will रुको क्रम ever.
 *
 * The caller is expected to perक्रमm the necessary locking.
 *
 * Returns:
 *   %-ETIMEDOUT	समयout occurred
 *   16-bit data	success
 */
पूर्णांक ssp_पढ़ो_word(u16 *data)
अणु
	पूर्णांक समयout = TIMEOUT;

	जबतक (!(Ser4SSSR & SSSR_RNE)) अणु
	        अगर (!--समयout)
	        	वापस -ETIMEDOUT;
		cpu_relax();
	पूर्ण

	*data = (u16)Ser4SSDR;

	वापस 0;
पूर्ण

/**
 * ssp_flush - flush the transmit and receive FIFOs
 *
 * Wait क्रम the SSP to idle, and ensure that the receive FIFO
 * is empty.
 *
 * The caller is expected to perक्रमm the necessary locking.
 *
 * Returns:
 *   %-ETIMEDOUT	समयout occurred
 *   0			success
 */
पूर्णांक ssp_flush(व्योम)
अणु
	पूर्णांक समयout = TIMEOUT * 2;

	करो अणु
		जबतक (Ser4SSSR & SSSR_RNE) अणु
		        अगर (!--समयout)
		        	वापस -ETIMEDOUT;
			(व्योम) Ser4SSDR;
		पूर्ण
	        अगर (!--समयout)
	        	वापस -ETIMEDOUT;
	पूर्ण जबतक (Ser4SSSR & SSSR_BSY);

	वापस 0;
पूर्ण

/**
 * ssp_enable - enable the SSP port
 *
 * Turn on the SSP port.
 */
व्योम ssp_enable(व्योम)
अणु
	Ser4SSCR0 |= SSCR0_SSE;
पूर्ण

/**
 * ssp_disable - shut करोwn the SSP port
 *
 * Turn off the SSP port, optionally घातering it करोwn.
 */
व्योम ssp_disable(व्योम)
अणु
	Ser4SSCR0 &= ~SSCR0_SSE;
पूर्ण

/**
 * ssp_save_state - save the SSP configuration
 * @ssp: poपूर्णांकer to काष्ठाure to save SSP configuration
 *
 * Save the configured SSP state क्रम suspend.
 */
व्योम ssp_save_state(काष्ठा ssp_state *ssp)
अणु
	ssp->cr0 = Ser4SSCR0;
	ssp->cr1 = Ser4SSCR1;

	Ser4SSCR0 &= ~SSCR0_SSE;
पूर्ण

/**
 * ssp_restore_state - restore a previously saved SSP configuration
 * @ssp: poपूर्णांकer to configuration saved by ssp_save_state
 *
 * Restore the SSP configuration saved previously by ssp_save_state.
 */
व्योम ssp_restore_state(काष्ठा ssp_state *ssp)
अणु
	Ser4SSSR = SSSR_ROR;

	Ser4SSCR0 = ssp->cr0 & ~SSCR0_SSE;
	Ser4SSCR1 = ssp->cr1;
	Ser4SSCR0 = ssp->cr0;
पूर्ण

/**
 * ssp_init - setup the SSP port
 *
 * initialise and claim resources क्रम the SSP port.
 *
 * Returns:
 *   %-ENODEV	अगर the SSP port is unavailable
 *   %-EBUSY	अगर the resources are alपढ़ोy in use
 *   %0		on success
 */
पूर्णांक ssp_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!(PPAR & PPAR_SPR) && (Ser4MCCR0 & MCCR0_MCE))
		वापस -ENODEV;

	अगर (!request_mem_region(__PREG(Ser4SSCR0), 0x18, "SSP")) अणु
		वापस -EBUSY;
	पूर्ण

	Ser4SSSR = SSSR_ROR;

	ret = request_irq(IRQ_Ser4SSP, ssp_पूर्णांकerrupt, 0, "SSP", शून्य);
	अगर (ret)
		जाओ out_region;

	वापस 0;

 out_region:
	release_mem_region(__PREG(Ser4SSCR0), 0x18);
	वापस ret;
पूर्ण

/**
 * ssp_निकास - unकरो the effects of ssp_init
 *
 * release and मुक्त resources क्रम the SSP port.
 */
व्योम ssp_निकास(व्योम)
अणु
	Ser4SSCR0 &= ~SSCR0_SSE;

	मुक्त_irq(IRQ_Ser4SSP, शून्य);
	release_mem_region(__PREG(Ser4SSCR0), 0x18);
पूर्ण

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("SA11x0 SSP PIO driver");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(ssp_ग_लिखो_word);
EXPORT_SYMBOL(ssp_पढ़ो_word);
EXPORT_SYMBOL(ssp_flush);
EXPORT_SYMBOL(ssp_enable);
EXPORT_SYMBOL(ssp_disable);
EXPORT_SYMBOL(ssp_save_state);
EXPORT_SYMBOL(ssp_restore_state);
EXPORT_SYMBOL(ssp_init);
EXPORT_SYMBOL(ssp_निकास);
