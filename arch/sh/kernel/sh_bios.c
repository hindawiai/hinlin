<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  C पूर्णांकerface क्रम trapping पूर्णांकo the standard LinuxSH BIOS.
 *
 *  Copyright (C) 2000 Greg Banks, Mitch Davis
 *  Copyright (C) 1999, 2000  Niibe Yutaka
 *  Copyright (C) 2002  M. R. Brown
 *  Copyright (C) 2004 - 2010  Paul Mundt
 */
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <यंत्र/sh_मूलप्रण.स>

#घोषणा BIOS_CALL_CONSOLE_WRITE		0
#घोषणा BIOS_CALL_ETH_NODE_ADDR		10
#घोषणा BIOS_CALL_SHUTDOWN		11
#घोषणा BIOS_CALL_GDB_DETACH		0xff

व्योम *gdb_vbr_vector = शून्य;

अटल अंतरभूत दीर्घ sh_bios_call(दीर्घ func, दीर्घ arg0, दीर्घ arg1, दीर्घ arg2,
				    दीर्घ arg3)
अणु
	रेजिस्टर दीर्घ r0 __यंत्र__("r0") = func;
	रेजिस्टर दीर्घ r4 __यंत्र__("r4") = arg0;
	रेजिस्टर दीर्घ r5 __यंत्र__("r5") = arg1;
	रेजिस्टर दीर्घ r6 __यंत्र__("r6") = arg2;
	रेजिस्टर दीर्घ r7 __यंत्र__("r7") = arg3;

	अगर (!gdb_vbr_vector)
		वापस -ENOSYS;

	__यंत्र__ __अस्थिर__("trapa	#0x3f":"=z"(r0)
			     :"0"(r0), "r"(r4), "r"(r5), "r"(r6), "r"(r7)
			     :"memory");
	वापस r0;
पूर्ण

व्योम sh_bios_console_ग_लिखो(स्थिर अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	sh_bios_call(BIOS_CALL_CONSOLE_WRITE, (दीर्घ)buf, (दीर्घ)len, 0, 0);
पूर्ण

व्योम sh_bios_gdb_detach(व्योम)
अणु
	sh_bios_call(BIOS_CALL_GDB_DETACH, 0, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sh_bios_gdb_detach);

व्योम sh_bios_get_node_addr(अचिन्हित अक्षर *node_addr)
अणु
	sh_bios_call(BIOS_CALL_ETH_NODE_ADDR, 0, (दीर्घ)node_addr, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sh_bios_get_node_addr);

व्योम sh_bios_shutकरोwn(अचिन्हित पूर्णांक how)
अणु
	sh_bios_call(BIOS_CALL_SHUTDOWN, how, 0, 0, 0);
पूर्ण

/*
 * Read the old value of the VBR रेजिस्टर to initialise the vector
 * through which debug and BIOS traps are delegated by the Linux trap
 * handler.
 */
व्योम sh_bios_vbr_init(व्योम)
अणु
	अचिन्हित दीर्घ vbr;

	अगर (unlikely(gdb_vbr_vector))
		वापस;

	__यंत्र__ __अस्थिर__ ("stc vbr, %0" : "=r" (vbr));

	अगर (vbr) अणु
		gdb_vbr_vector = (व्योम *)(vbr + 0x100);
		prपूर्णांकk(KERN_NOTICE "Setting GDB trap vector to %p\n",
		       gdb_vbr_vector);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_NOTICE "SH-BIOS not detected\n");
पूर्ण

/**
 * sh_bios_vbr_reload - Re-load the प्रणाली VBR from the BIOS vector.
 *
 * This can be used by save/restore code to reinitialize the प्रणाली VBR
 * from the fixed BIOS VBR. A no-op अगर no BIOS VBR is known.
 */
व्योम sh_bios_vbr_reload(व्योम)
अणु
	अगर (gdb_vbr_vector)
		__यंत्र__ __अस्थिर__ (
			"ldc %0, vbr"
			:
			: "r" (((अचिन्हित दीर्घ) gdb_vbr_vector) - 0x100)
			: "memory"
		);
पूर्ण

#अगर_घोषित CONFIG_EARLY_PRINTK
/*
 *	Prपूर्णांक a string through the BIOS
 */
अटल व्योम sh_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				 अचिन्हित count)
अणु
	sh_bios_console_ग_लिखो(s, count);
पूर्ण

/*
 *	Setup initial baud/bits/parity. We करो two things here:
 *	- स्थिरruct a cflag setting क्रम the first rs_खोलो()
 *	- initialize the serial port
 *	Return non-zero अगर we didn't find a serial port.
 */
अटल पूर्णांक __init sh_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	पूर्णांक	cflag = CREAD | HUPCL | CLOCAL;

	/*
	 *	Now स्थिरruct a cflag setting.
	 *	TODO: this is a totally bogus cflag, as we have
	 *	no idea what serial settings the BIOS is using, or
	 *	even अगर its using the serial port at all.
	 */
	cflag |= B115200 | CS8 | /*no parity*/0;

	co->cflag = cflag;

	वापस 0;
पूर्ण

अटल काष्ठा console bios_console = अणु
	.name		= "bios",
	.ग_लिखो		= sh_console_ग_लिखो,
	.setup		= sh_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
पूर्ण;

अटल पूर्णांक __init setup_early_prपूर्णांकk(अक्षर *buf)
अणु
	पूर्णांक keep_early = 0;

	अगर (!buf)
		वापस 0;

	अगर (म_माला(buf, "keep"))
		keep_early = 1;

	अगर (!म_भेदन(buf, "bios", 4))
		early_console = &bios_console;

	अगर (likely(early_console)) अणु
		अगर (keep_early)
			early_console->flags &= ~CON_BOOT;
		अन्यथा
			early_console->flags |= CON_BOOT;
		रेजिस्टर_console(early_console);
	पूर्ण

	वापस 0;
पूर्ण
early_param("earlyprintk", setup_early_prपूर्णांकk);
#पूर्ण_अगर
