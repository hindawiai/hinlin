<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* toshiba.c -- Linux driver क्रम accessing the SMM on Toshiba laptops
 *
 * Copyright (c) 1996-2001  Jonathan A. Buzzard (jonathan@buzzard.org.uk)
 *
 * Valuable assistance and patches from:
 *     Tom May <tom@you-bastards.com>
 *     Rob Napier <rnapier@employees.org>
 *
 * Fn status port numbers क्रम machine ID's courtesy of
 *     0xfc02: Scott Eisert <scott.e@sky-eye.com>
 *     0xfc04: Steve VanDevender <stevev@efn.org>
 *     0xfc08: Garth Berry <garth@itsbruce.net>
 *     0xfc0a: Egbert Eich <eich@xमुक्त86.org>
 *     0xfc10: Andrew Lofthouse <Andrew.Lofthouse@robins.af.mil>
 *     0xfc11: Spencer Olson <solson@novell.com>
 *     0xfc13: Claudius Frankewitz <kryp@gmx.de>
 *     0xfc15: Tom May <tom@you-bastards.com>
 *     0xfc17: Dave Konrad <konrad@xenia.it>
 *     0xfc1a: George Betzos <betzos@engr.colostate.edu>
 *     0xfc1b: Munemasa Wada <munemasa@jnovel.co.jp>
 *     0xfc1d: Arthur Liu <armie@slap.mine.nu>
 *     0xfc5a: Jacques L'helgoualc'h <lhh@मुक्त.fr>
 *     0xfcd1: Mr. Dave Konrad <konrad@xenia.it>
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *
 *   This code is covered by the GNU GPL and you are मुक्त to make any
 *   changes you wish to it under the terms of the license. However the
 *   code has the potential to render your computer and/or someone अन्यथा's
 *   unusable. Please proceed with care when modअगरying the code.
 *
 * Note: Unक्रमtunately the laptop hardware can बंद the System Configuration
 *       Interface on it's own accord. It is thereक्रमe necessary क्रम *all*
 *       programs using this driver to be aware that *any* SCI call can fail at
 *       *any* समय. It is up to any program to be aware of this eventuality
 *       and take appropriate steps.
 *
 * The inक्रमmation used to ग_लिखो this driver has been obtained by reverse
 * engineering the software supplied by Toshiba क्रम their portable computers in
 * strict accordance with the European Council Directive 92/250/EEC on the legal
 * protection of computer programs, and it's implementation पूर्णांकo English Law by
 * the Copyright (Computer Programs) Regulations 1992 (S.I. 1992 No.3233).
 */

#घोषणा TOSH_VERSION "1.11 26/9/2001"
#घोषणा TOSH_DEBUG 0

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/ioport.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mutex.h>
#समावेश <linux/toshiba.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonathan Buzzard <jonathan@buzzard.org.uk>");
MODULE_DESCRIPTION("Toshiba laptop SMM driver");

अटल DEFINE_MUTEX(tosh_mutex);
अटल पूर्णांक tosh_fn;
module_param_named(fn, tosh_fn, पूर्णांक, 0);
MODULE_PARM_DESC(fn, "User specified Fn key detection port");

अटल पूर्णांक tosh_id;
अटल पूर्णांक tosh_bios;
अटल पूर्णांक tosh_date;
अटल पूर्णांक tosh_sci;
अटल पूर्णांक tosh_fan;

अटल दीर्घ tosh_ioctl(काष्ठा file *, अचिन्हित पूर्णांक,
	अचिन्हित दीर्घ);


अटल स्थिर काष्ठा file_operations tosh_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= tosh_ioctl,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice tosh_device = अणु
	TOSH_MINOR_DEV,
	"toshiba",
	&tosh_fops
पूर्ण;

/*
 * Read the Fn key status
 */
#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक tosh_fn_status(व्योम)
अणु
        अचिन्हित अक्षर scan;
	अचिन्हित दीर्घ flags;

	अगर (tosh_fn!=0) अणु
		scan = inb(tosh_fn);
	पूर्ण अन्यथा अणु
		local_irq_save(flags);
		outb(0x8e, 0xe4);
		scan = inb(0xe5);
		local_irq_restore(flags);
	पूर्ण

        वापस (पूर्णांक) scan;
पूर्ण
#पूर्ण_अगर


/*
 * For the Portage 610CT and the Tecra 700CS/700CDT emulate the HCI fan function
 */
अटल पूर्णांक tosh_emulate_fan(SMMRegisters *regs)
अणु
	अचिन्हित दीर्घ eax,ecx,flags;
	अचिन्हित अक्षर al;

	eax = regs->eax & 0xff00;
	ecx = regs->ecx & 0xffff;

	/* Portage 610CT */

	अगर (tosh_id==0xfccb) अणु
		अगर (eax==0xfe00) अणु
			/* fan status */
			local_irq_save(flags);
			outb(0xbe, 0xe4);
			al = inb(0xe5);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = (अचिन्हित पूर्णांक) (al & 0x01);
		पूर्ण
		अगर ((eax==0xff00) && (ecx==0x0000)) अणु
			/* fan off */
			local_irq_save(flags);
			outb(0xbe, 0xe4);
			al = inb(0xe5);
			outb(0xbe, 0xe4);
			outb (al | 0x01, 0xe5);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = 0x00;
		पूर्ण
		अगर ((eax==0xff00) && (ecx==0x0001)) अणु
			/* fan on */
			local_irq_save(flags);
			outb(0xbe, 0xe4);
			al = inb(0xe5);
			outb(0xbe, 0xe4);
			outb(al & 0xfe, 0xe5);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = 0x01;
		पूर्ण
	पूर्ण

	/* Tecra 700CS/CDT */

	अगर (tosh_id==0xfccc) अणु
		अगर (eax==0xfe00) अणु
			/* fan status */
			local_irq_save(flags);
			outb(0xe0, 0xe4);
			al = inb(0xe5);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = al & 0x01;
		पूर्ण
		अगर ((eax==0xff00) && (ecx==0x0000)) अणु
			/* fan off */
			local_irq_save(flags);
			outb(0xe0, 0xe4);
			al = inb(0xe5);
			outw(0xe0 | ((al & 0xfe) << 8), 0xe4);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = 0x00;
		पूर्ण
		अगर ((eax==0xff00) && (ecx==0x0001)) अणु
			/* fan on */
			local_irq_save(flags);
			outb(0xe0, 0xe4);
			al = inb(0xe5);
			outw(0xe0 | ((al | 0x01) << 8), 0xe4);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = 0x01;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Put the laptop पूर्णांकo System Management Mode
 */
पूर्णांक tosh_smm(SMMRegisters *regs)
अणु
	पूर्णांक eax;

	यंत्र ("# load the values into the registers\n\t" \
		"pushl %%eax\n\t" \
		"movl 0(%%eax),%%edx\n\t" \
		"push %%edx\n\t" \
		"movl 4(%%eax),%%ebx\n\t" \
		"movl 8(%%eax),%%ecx\n\t" \
		"movl 12(%%eax),%%edx\n\t" \
		"movl 16(%%eax),%%esi\n\t" \
		"movl 20(%%eax),%%edi\n\t" \
		"popl %%eax\n\t" \
		"# call the System Management mode\n\t" \
		"inb $0xb2,%%al\n\t"
		"# fill out the memory with the values in the registers\n\t" \
		"xchgl %%eax,(%%esp)\n\t"
		"movl %%ebx,4(%%eax)\n\t" \
		"movl %%ecx,8(%%eax)\n\t" \
		"movl %%edx,12(%%eax)\n\t" \
		"movl %%esi,16(%%eax)\n\t" \
		"movl %%edi,20(%%eax)\n\t" \
		"popl %%edx\n\t" \
		"movl %%edx,0(%%eax)\n\t" \
		"# setup the return value to the carry flag\n\t" \
		"lahf\n\t" \
		"shrl $8,%%eax\n\t" \
		"andl $1,%%eax\n" \
		: "=a" (eax)
		: "a" (regs)
		: "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory");

	वापस eax;
पूर्ण
EXPORT_SYMBOL(tosh_smm);


अटल दीर्घ tosh_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	SMMRegisters regs;
	SMMRegisters __user *argp = (SMMRegisters __user *)arg;
	अचिन्हित लघु ax,bx;
	पूर्णांक err;

	अगर (!argp)
		वापस -EINVAL;

	अगर (copy_from_user(&regs, argp, माप(SMMRegisters)))
		वापस -EFAULT;

	चयन (cmd) अणु
		हाल TOSH_SMM:
			ax = regs.eax & 0xff00;
			bx = regs.ebx & 0xffff;
			/* block HCI calls to पढ़ो/ग_लिखो memory & PCI devices */
			अगर (((ax==0xff00) || (ax==0xfe00)) && (bx>0x0069))
				वापस -EINVAL;

			/* करो we need to emulate the fan ? */
			mutex_lock(&tosh_mutex);
			अगर (tosh_fan==1) अणु
				अगर (((ax==0xf300) || (ax==0xf400)) && (bx==0x0004)) अणु
					err = tosh_emulate_fan(&regs);
					mutex_unlock(&tosh_mutex);
					अवरोध;
				पूर्ण
			पूर्ण
			err = tosh_smm(&regs);
			mutex_unlock(&tosh_mutex);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

        अगर (copy_to_user(argp, &regs, माप(SMMRegisters)))
        	वापस -EFAULT;

	वापस (err==0) ? 0:-EINVAL;
पूर्ण


/*
 * Prपूर्णांक the inक्रमmation क्रम /proc/toshiba
 */
#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक proc_toshiba_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक key;

	key = tosh_fn_status();

	/* Arguments
	     0) Linux driver version (this will change अगर क्रमmat changes)
	     1) Machine ID
	     2) SCI version
	     3) BIOS version (major, minor)
	     4) BIOS date (in SCI date क्रमmat)
	     5) Fn Key status
	*/
	seq_म_लिखो(m, "1.1 0x%04x %d.%d %d.%d 0x%04x 0x%02x\n",
		tosh_id,
		(tosh_sci & 0xff00)>>8,
		tosh_sci & 0xff,
		(tosh_bios & 0xff00)>>8,
		tosh_bios & 0xff,
		tosh_date,
		key);
	वापस 0;
पूर्ण
#पूर्ण_अगर


/*
 * Determine which port to use क्रम the Fn key status
 */
अटल व्योम tosh_set_fn_port(व्योम)
अणु
	चयन (tosh_id) अणु
		हाल 0xfc02: हाल 0xfc04: हाल 0xfc09: हाल 0xfc0a: हाल 0xfc10:
		हाल 0xfc11: हाल 0xfc13: हाल 0xfc15: हाल 0xfc1a: हाल 0xfc1b:
		हाल 0xfc5a:
			tosh_fn = 0x62;
			अवरोध;
		हाल 0xfc08: हाल 0xfc17: हाल 0xfc1d: हाल 0xfcd1: हाल 0xfce0:
		हाल 0xfce2:
			tosh_fn = 0x68;
			अवरोध;
		शेष:
			tosh_fn = 0x00;
			अवरोध;
	पूर्ण

	वापस;
पूर्ण


/*
 * Get the machine identअगरication number of the current model
 */
अटल पूर्णांक tosh_get_machine_id(व्योम __iomem *bios)
अणु
	पूर्णांक id;
	SMMRegisters regs;
	अचिन्हित लघु bx,cx;
	अचिन्हित दीर्घ address;

	id = (0x100*(पूर्णांक) पढ़ोb(bios+0xfffe))+((पूर्णांक) पढ़ोb(bios+0xfffa));

	/* करो we have a SCTTable machine identication number on our hands */

	अगर (id==0xfc2f) अणु

		/* start by getting a poपूर्णांकer पूर्णांकo the BIOS */

		regs.eax = 0xc000;
		regs.ebx = 0x0000;
		regs.ecx = 0x0000;
		tosh_smm(&regs);
		bx = (अचिन्हित लघु) (regs.ebx & 0xffff);

		/* At this poपूर्णांक in the Toshiba routines under MS Winकरोws
		   the bx रेजिस्टर holds 0xe6f5. However my code is producing
		   a dअगरferent value! For the समय being I will just fudge the
		   value. This has been verअगरied on a Satellite Pro 430CDT,
		   Tecra 750CDT, Tecra 780DVD and Satellite 310CDT. */
#अगर TOSH_DEBUG
		pr_debug("toshiba: debugging ID ebx=0x%04x\n", regs.ebx);
#पूर्ण_अगर
		bx = 0xe6f5;

		/* now twiddle with our poपूर्णांकer a bit */

		address = bx;
		cx = पढ़ोw(bios + address);
		address = 9+bx+cx;
		cx = पढ़ोw(bios + address);
		address = 0xa+cx;
		cx = पढ़ोw(bios + address);

		/* now स्थिरruct our machine identअगरication number */

		id = ((cx & 0xff)<<8)+((cx & 0xff00)>>8);
	पूर्ण

	वापस id;
पूर्ण


/*
 * Probe क्रम the presence of a Toshiba laptop
 *
 *   वापसs and non-zero अगर unable to detect the presence of a Toshiba
 *   laptop, otherwise zero and determines the Machine ID, BIOS version and
 *   date, and SCI version.
 */
अटल पूर्णांक tosh_probe(व्योम)
अणु
	पूर्णांक i,major,minor,day,year,month,flag;
	अचिन्हित अक्षर signature[7] = अणु 0x54,0x4f,0x53,0x48,0x49,0x42,0x41 पूर्ण;
	SMMRegisters regs;
	व्योम __iomem *bios = ioremap(0xf0000, 0x10000);

	अगर (!bios)
		वापस -ENOMEM;

	/* extra sanity check क्रम the string "TOSHIBA" in the BIOS because
	   some machines that are not Toshiba's pass the next test */

	क्रम (i=0;i<7;i++) अणु
		अगर (पढ़ोb(bios+0xe010+i)!=signature[i]) अणु
			pr_err("toshiba: not a supported Toshiba laptop\n");
			iounmap(bios);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* call the Toshiba SCI support check routine */

	regs.eax = 0xf0f0;
	regs.ebx = 0x0000;
	regs.ecx = 0x0000;
	flag = tosh_smm(&regs);

	/* अगर this is not a Toshiba laptop carry flag is set and ah=0x86 */

	अगर ((flag==1) || ((regs.eax & 0xff00)==0x8600)) अणु
		pr_err("toshiba: not a supported Toshiba laptop\n");
		iounmap(bios);
		वापस -ENODEV;
	पूर्ण

	/* अगर we get this far then we are running on a Toshiba (probably)! */

	tosh_sci = regs.edx & 0xffff;

	/* next get the machine ID of the current laptop */

	tosh_id = tosh_get_machine_id(bios);

	/* get the BIOS version */

	major = पढ़ोb(bios+0xe009)-'0';
	minor = ((पढ़ोb(bios+0xe00b)-'0')*10)+(readb(bios+0xe00c)-'0');
	tosh_bios = (major*0x100)+minor;

	/* get the BIOS date */

	day = ((पढ़ोb(bios+0xfff5)-'0')*10)+(readb(bios+0xfff6)-'0');
	month = ((पढ़ोb(bios+0xfff8)-'0')*10)+(readb(bios+0xfff9)-'0');
	year = ((पढ़ोb(bios+0xfffb)-'0')*10)+(readb(bios+0xfffc)-'0');
	tosh_date = (((year-90) & 0x1f)<<10) | ((month & 0xf)<<6)
		| ((day & 0x1f)<<1);


	/* in theory we should check the ports we are going to use क्रम the
	   fn key detection (and the fan on the Portage 610/Tecra700), and
	   then request them to stop other drivers using them. However as
	   the keyboard driver grअसल 0x60-0x6f and the pic driver grअसल
	   0xa0-0xbf we can't. We just have to live dangerously and use the
	   ports anyway, oh boy! */

	/* करो we need to emulate the fan? */

	अगर ((tosh_id==0xfccb) || (tosh_id==0xfccc))
		tosh_fan = 1;

	iounmap(bios);

	वापस 0;
पूर्ण

अटल पूर्णांक __init toshiba_init(व्योम)
अणु
	पूर्णांक retval;
	/* are we running on a Toshiba laptop */

	अगर (tosh_probe())
		वापस -ENODEV;

	pr_info("Toshiba System Management Mode driver v" TOSH_VERSION "\n");

	/* set the port to use क्रम Fn status अगर not specअगरied as a parameter */
	अगर (tosh_fn==0x00)
		tosh_set_fn_port();

	/* रेजिस्टर the device file */
	retval = misc_रेजिस्टर(&tosh_device);
	अगर (retval < 0)
		वापस retval;

#अगर_घोषित CONFIG_PROC_FS
	अणु
		काष्ठा proc_dir_entry *pde;

		pde = proc_create_single("toshiba", 0, शून्य, proc_toshiba_show);
		अगर (!pde) अणु
			misc_deरेजिस्टर(&tosh_device);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __निकास toshiba_निकास(व्योम)
अणु
	हटाओ_proc_entry("toshiba", शून्य);
	misc_deरेजिस्टर(&tosh_device);
पूर्ण

module_init(toshiba_init);
module_निकास(toshiba_निकास);

