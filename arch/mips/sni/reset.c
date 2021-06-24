<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/mips/sni/process.c
 *
 *  Reset a SNI machine.
 */
#समावेश <linux/delay.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/sni.h>

/*
 * This routine reboots the machine by asking the keyboard
 * controller to pulse the reset-line low. We try that क्रम a जबतक,
 * and अगर it करोesn't work, we करो some other stupid things.
 */
अटल अंतरभूत व्योम kb_रुको(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x10000; i++)
		अगर ((inb_p(0x64) & 0x02) == 0)
			अवरोध;
पूर्ण

/* XXX This ends up at the ARC firmware prompt ...  */
व्योम sni_machine_restart(अक्षर *command)
अणु
	पूर्णांक i;

	/* This करोes a normal via the keyboard controller like a PC.
	   We can करो that easier ...  */
	local_irq_disable();
	क्रम (;;) अणु
		क्रम (i = 0; i < 100; i++) अणु
			kb_रुको();
			udelay(50);
			outb_p(0xfe, 0x64);	 /* pulse reset low */
			udelay(50);
		पूर्ण
	पूर्ण
पूर्ण

व्योम sni_machine_घातer_off(व्योम)
अणु
	*(अस्थिर अचिन्हित अक्षर *)PCIMT_CSWCSM = 0xfd;
पूर्ण
