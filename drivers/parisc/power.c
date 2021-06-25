<शैली गुरु>
/*
 * linux/drivers/parisc/घातer.c
 * HP PARISC soft घातer चयन support driver
 *
 * Copyright (c) 2001-2007 Helge Deller <deller@gmx.de>
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *
 *
 *  HINT:
 *  Support of the soft घातer चयन button may be enabled or disabled at
 *  runसमय through the "/proc/sys/kernel/power" procfs entry.
 */ 

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/led.h>

#घोषणा DRIVER_NAME  "powersw"
#घोषणा KTHREAD_NAME "kpowerswd"

/* how often should the घातer button be polled ? */
#घोषणा POWERSWITCH_POLL_PER_SEC 2

/* how दीर्घ करोes the घातer button needs to be करोwn until we react ? */
#घोषणा POWERSWITCH_DOWN_SEC 2

/* assembly code to access special रेजिस्टरs */
/* taken from PCXL ERS page 82 */
#घोषणा DIAG_CODE(code)		(0x14000000 + ((code)<<5))

#घोषणा MFCPU_X(rDiagReg, t_ch, t_th, code) \
	(DIAG_CODE(code) + ((rDiagReg)<<21) + ((t_ch)<<16) + ((t_th)<<0) )
	
#घोषणा MTCPU(dr, gr)		MFCPU_X(dr, gr,  0, 0x12)       /* move value of gr to dr[dr] */
#घोषणा MFCPU_C(dr, gr)		MFCPU_X(dr, gr,  0, 0x30)	/* क्रम dr0 and dr8 only ! */
#घोषणा MFCPU_T(dr, gr)		MFCPU_X(dr,  0, gr, 0xa0)	/* all dr except dr0 and dr8 */
	
#घोषणा __getDIAG(dr) ( अणु 			\
        रेजिस्टर अचिन्हित दीर्घ __res यंत्र("r28");\
	 __यंत्र__ __अस्थिर__ (			\
		".word %1" : "=&r" (__res) : "i" (MFCPU_T(dr,28) ) \
	);					\
	__res;					\
पूर्ण )

/* local shutकरोwn counter */
अटल पूर्णांक shutकरोwn_समयr __पढ़ो_mostly;

/* check, give feedback and start shutकरोwn after one second */
अटल व्योम process_shutकरोwn(व्योम)
अणु
	अगर (shutकरोwn_समयr == 0)
		prपूर्णांकk(KERN_ALERT KTHREAD_NAME ": Shutdown requested...\n");

	shutकरोwn_समयr++;
	
	/* रुको until the button was pressed क्रम 1 second */
	अगर (shutकरोwn_समयr == (POWERSWITCH_DOWN_SEC*POWERSWITCH_POLL_PER_SEC)) अणु
		अटल स्थिर अक्षर msg[] = "Shutting down...";
		prपूर्णांकk(KERN_INFO KTHREAD_NAME ": %s\n", msg);
		lcd_prपूर्णांक(msg);

		/* send समाप्त संकेत */
		अगर (समाप्त_cad_pid(संक_विघ्न, 1)) अणु
			/* just in हाल समाप्तing init process failed */
			machine_घातer_off();
		पूर्ण
	पूर्ण
पूर्ण


/* मुख्य घातer चयन task काष्ठा */
अटल काष्ठा task_काष्ठा *घातer_task;

/* filename in /proc which can be used to enable/disable the घातer चयन */
#घोषणा SYSCTL_खाताNAME	"sys/kernel/power"

/* soft घातer चयन enabled/disabled */
पूर्णांक pwrsw_enabled __पढ़ो_mostly = 1;

/* मुख्य kernel thपढ़ो worker. It polls the button state */
अटल पूर्णांक kघातerswd(व्योम *param)
अणु
	__set_current_state(TASK_RUNNING);

	करो अणु
		पूर्णांक button_not_pressed;
		अचिन्हित दीर्घ soft_घातer_reg = (अचिन्हित दीर्घ) param;

		schedule_समयout_पूर्णांकerruptible(pwrsw_enabled ? HZ : HZ/POWERSWITCH_POLL_PER_SEC);

		अगर (unlikely(!pwrsw_enabled))
			जारी;

		अगर (soft_घातer_reg) अणु
			/*
			 * Non-Gecko-style machines:
			 * Check the घातer चयन status which is पढ़ो from the
			 * real I/O location at soft_घातer_reg.
			 * Bit 31 ("the lowest bit) is the status of the घातer चयन.
			 * This bit is "1" अगर the button is NOT pressed.
			 */
			button_not_pressed = (gsc_पढ़ोl(soft_घातer_reg) & 0x1);
		पूर्ण अन्यथा अणु
			/*
			 * On gecko style machines (e.g. 712/xx and 715/xx) 
			 * the घातer चयन status is stored in Bit 0 ("the highest bit")
			 * of CPU diagnose रेजिस्टर 25.
			 * Warning: Some machines never reset the DIAG flag, even अगर
			 * the button has been released again.
			 */
			button_not_pressed = (__getDIAG(25) & 0x80000000);
		पूर्ण

		अगर (likely(button_not_pressed)) अणु
			अगर (unlikely(shutकरोwn_समयr && /* aव्योम writing अगर not necessary */
				shutकरोwn_समयr < (POWERSWITCH_DOWN_SEC*POWERSWITCH_POLL_PER_SEC))) अणु
				shutकरोwn_समयr = 0;
				prपूर्णांकk(KERN_INFO KTHREAD_NAME ": Shutdown request aborted.\n");
			पूर्ण
		पूर्ण अन्यथा
			process_shutकरोwn();


	पूर्ण जबतक (!kthपढ़ो_should_stop());

	वापस 0;
पूर्ण


/*
 * घातerfail पूर्णांकerruption handler (irq IRQ_FROM_REGION(CPU_IRQ_REGION)+2) 
 */
#अगर 0
अटल व्योम घातerfail_पूर्णांकerrupt(पूर्णांक code, व्योम *x)
अणु
	prपूर्णांकk(KERN_CRIT "POWERFAIL INTERRUPTION !\n");
	घातeroff();
पूर्ण
#पूर्ण_अगर




/* parisc_panic_event() is called by the panic handler.
 * As soon as a panic occurs, our tasklets above will not be
 * executed any दीर्घer. This function then re-enables the 
 * soft-घातer चयन and allows the user to चयन off the प्रणाली
 */
अटल पूर्णांक parisc_panic_event(काष्ठा notअगरier_block *this,
		अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	/* re-enable the soft-घातer चयन */
	pdc_soft_घातer_button(0);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block parisc_panic_block = अणु
	.notअगरier_call	= parisc_panic_event,
	.priority	= पूर्णांक_उच्च,
पूर्ण;


अटल पूर्णांक __init घातer_init(व्योम)
अणु
	अचिन्हित दीर्घ ret;
	अचिन्हित दीर्घ soft_घातer_reg;

#अगर 0
	request_irq( IRQ_FROM_REGION(CPU_IRQ_REGION)+2, &घातerfail_पूर्णांकerrupt,
		0, "powerfail", शून्य);
#पूर्ण_अगर

	/* enable the soft घातer चयन अगर possible */
	ret = pdc_soft_घातer_info(&soft_घातer_reg);
	अगर (ret == PDC_OK)
		ret = pdc_soft_घातer_button(1);
	अगर (ret != PDC_OK)
		soft_घातer_reg = -1UL;
	
	चयन (soft_घातer_reg) अणु
	हाल 0:		prपूर्णांकk(KERN_INFO DRIVER_NAME ": Gecko-style soft power switch enabled.\n");
			अवरोध;
			
	हाल -1UL:	prपूर्णांकk(KERN_INFO DRIVER_NAME ": Soft power switch support not available.\n");
			वापस -ENODEV;
	
	शेष:	prपूर्णांकk(KERN_INFO DRIVER_NAME ": Soft power switch at 0x%08lx enabled.\n",
				soft_घातer_reg);
	पूर्ण

	घातer_task = kthपढ़ो_run(kघातerswd, (व्योम*)soft_घातer_reg, KTHREAD_NAME);
	अगर (IS_ERR(घातer_task)) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": thread creation failed.  Driver not loaded.\n");
		pdc_soft_घातer_button(0);
		वापस -EIO;
	पूर्ण

	/* Register a call क्रम panic conditions. */
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
			&parisc_panic_block);

	वापस 0;
पूर्ण

अटल व्योम __निकास घातer_निकास(व्योम)
अणु
	kthपढ़ो_stop(घातer_task);

	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
			&parisc_panic_block);

	pdc_soft_घातer_button(0);
पूर्ण

arch_initcall(घातer_init);
module_निकास(घातer_निकास);


MODULE_AUTHOR("Helge Deller <deller@gmx.de>");
MODULE_DESCRIPTION("Soft power switch driver");
MODULE_LICENSE("Dual BSD/GPL");
