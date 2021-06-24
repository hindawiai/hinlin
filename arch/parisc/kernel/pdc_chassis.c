<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 
 *    पूर्णांकerfaces to Chassis Codes via PDC (firmware)
 *
 *    Copyright (C) 2002 Laurent Canet <canetl@esiee.fr>
 *    Copyright (C) 2002-2006 Thibaut VARENE <varenet@parisc-linux.org>
 *
 *    TODO: poll chassis warns, trigger (configurable) machine shutकरोwn when
 *    		needed.
 *    	    Find out how to get Chassis warnings out of PAT boxes?
 */

#अघोषित PDC_CHASSIS_DEBUG
#अगर_घोषित PDC_CHASSIS_DEBUG
#घोषणा DPRINTK(fmt, args...)	prपूर्णांकk(fmt, ## args)
#अन्यथा
#घोषणा DPRINTK(fmt, args...)
#पूर्ण_अगर

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cache.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/pdc_chassis.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/pdcpat.h>

#घोषणा PDC_CHASSIS_VER	"0.05"

#अगर_घोषित CONFIG_PDC_CHASSIS
अटल अचिन्हित पूर्णांक pdc_chassis_enabled __पढ़ो_mostly = 1;


/**
 * pdc_chassis_setup() - Enable/disable pdc_chassis code at boot समय.
 * @str configuration param: 0 to disable chassis log
 * @वापस 1
 */
 
अटल पूर्णांक __init pdc_chassis_setup(अक्षर *str)
अणु
	/*panic_समयout = simple_म_से_अदीर्घ(str, शून्य, 0);*/
	get_option(&str, &pdc_chassis_enabled);
	वापस 1;
पूर्ण
__setup("pdcchassis=", pdc_chassis_setup);


/** 
 * pdc_chassis_checkold() - Checks क्रम old PDC_CHASSIS compatibility
 * @pdc_chassis_old: 1 अगर old pdc chassis style
 * 
 * Currently, only E class and A180 are known to work with this.
 * Inspired by Christoph Plattner
 */
#अगर 0
अटल व्योम __init pdc_chassis_checkold(व्योम)
अणु
	चयन(CPU_HVERSION) अणु
		हाल 0x480:		/* E25 */
		हाल 0x481:		/* E35 */
		हाल 0x482:		/* E45 */
		हाल 0x483:		/* E55 */
		हाल 0x516:		/* A180 */
			अवरोध;

		शेष:
			अवरोध;
	पूर्ण
	DPRINTK(KERN_DEBUG "%s: pdc_chassis_checkold(); pdc_chassis_old = %d\n", __खाता__, pdc_chassis_old);
पूर्ण
#पूर्ण_अगर

/**
 * pdc_chassis_panic_event() - Called by the panic handler.
 *
 * As soon as a panic occurs, we should inक्रमm the PDC.
 */

अटल पूर्णांक pdc_chassis_panic_event(काष्ठा notअगरier_block *this,
		        अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_PANIC);
		वापस NOTIFY_DONE;
पूर्ण   


अटल काष्ठा notअगरier_block pdc_chassis_panic_block = अणु
	.notअगरier_call = pdc_chassis_panic_event,
	.priority = पूर्णांक_उच्च,
पूर्ण;


/**
 * parisc_reboot_event() - Called by the reboot handler.
 *
 * As soon as a reboot occurs, we should inक्रमm the PDC.
 */

अटल पूर्णांक pdc_chassis_reboot_event(काष्ठा notअगरier_block *this,
		        अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_SHUTDOWN);
		वापस NOTIFY_DONE;
पूर्ण   


अटल काष्ठा notअगरier_block pdc_chassis_reboot_block = अणु
	.notअगरier_call = pdc_chassis_reboot_event,
	.priority = पूर्णांक_उच्च,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PDC_CHASSIS */


/**
 * parisc_pdc_chassis_init() - Called at boot समय.
 */

व्योम __init parisc_pdc_chassis_init(व्योम)
अणु
#अगर_घोषित CONFIG_PDC_CHASSIS
	अगर (likely(pdc_chassis_enabled)) अणु
		DPRINTK(KERN_DEBUG "%s: parisc_pdc_chassis_init()\n", __खाता__);

		/* Let see अगर we have something to handle... */
		prपूर्णांकk(KERN_INFO "Enabling %s chassis codes support v%s\n",
				is_pdc_pat() ? "PDC_PAT" : "regular",
				PDC_CHASSIS_VER);

		/* initialize panic notअगरier chain */
		atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				&pdc_chassis_panic_block);

		/* initialize reboot notअगरier chain */
		रेजिस्टर_reboot_notअगरier(&pdc_chassis_reboot_block);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PDC_CHASSIS */
पूर्ण


/** 
 * pdc_chassis_send_status() - Sends a predefined message to the chassis,
 * and changes the front panel LEDs according to the new प्रणाली state
 * @retval: PDC call वापस value.
 *
 * Only machines with 64 bits PDC PAT and those reported in
 * pdc_chassis_checkold() are supported aपंचांग.
 * 
 * वापसs 0 अगर no error, -1 अगर no supported PDC is present or invalid message,
 * अन्यथा वापसs the appropriate PDC error code.
 * 
 * For a list of predefined messages, see यंत्र-parisc/pdc_chassis.h
 */

पूर्णांक pdc_chassis_send_status(पूर्णांक message)
अणु
	/* Maybe we should करो that in an other way ? */
	पूर्णांक retval = 0;
#अगर_घोषित CONFIG_PDC_CHASSIS
	अगर (likely(pdc_chassis_enabled)) अणु

		DPRINTK(KERN_DEBUG "%s: pdc_chassis_send_status(%d)\n", __खाता__, message);

#अगर_घोषित CONFIG_64BIT
		अगर (is_pdc_pat()) अणु
			चयन(message) अणु
				हाल PDC_CHASSIS_सूचीECT_BSTART:
					retval = pdc_pat_chassis_send_log(PDC_CHASSIS_PMSG_BSTART, PDC_CHASSIS_LSTATE_RUN_NORMAL);
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_BCOMPLETE:
					retval = pdc_pat_chassis_send_log(PDC_CHASSIS_PMSG_BCOMPLETE, PDC_CHASSIS_LSTATE_RUN_NORMAL);
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_SHUTDOWN:
					retval = pdc_pat_chassis_send_log(PDC_CHASSIS_PMSG_SHUTDOWN, PDC_CHASSIS_LSTATE_NONOS);
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_PANIC:
					retval = pdc_pat_chassis_send_log(PDC_CHASSIS_PMSG_PANIC, PDC_CHASSIS_LSTATE_RUN_CRASHREC);
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_LPMC:
					retval = pdc_pat_chassis_send_log(PDC_CHASSIS_PMSG_LPMC, PDC_CHASSIS_LSTATE_RUN_SYSINT);
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_HPMC:
					retval = pdc_pat_chassis_send_log(PDC_CHASSIS_PMSG_HPMC, PDC_CHASSIS_LSTATE_RUN_NCRIT);
					अवरोध;

				शेष:
					retval = -1;
			पूर्ण
		पूर्ण अन्यथा retval = -1;
#अन्यथा
		अगर (1) अणु
			चयन (message) अणु
				हाल PDC_CHASSIS_सूचीECT_BSTART:
					retval = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_INIT));
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_BCOMPLETE:
					retval = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_RUN));
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_SHUTDOWN:
					retval = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_SHUT));
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_HPMC:
				हाल PDC_CHASSIS_सूचीECT_PANIC:
					retval = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_FLT));
					अवरोध;

				हाल PDC_CHASSIS_सूचीECT_LPMC:
					retval = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_WARN));
					अवरोध;

				शेष:
					retval = -1;
			पूर्ण
		पूर्ण अन्यथा retval = -1;
#पूर्ण_अगर /* CONFIG_64BIT */
	पूर्ण	/* अगर (pdc_chassis_enabled) */
#पूर्ण_अगर /* CONFIG_PDC_CHASSIS */
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PDC_CHASSIS_WARN
#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक pdc_chassis_warn_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ warn;
	u32 warnreg;

	अगर (pdc_chassis_warn(&warn) != PDC_OK)
		वापस -EIO;

	warnreg = (warn & 0xFFFFFFFF);

	अगर ((warnreg >> 24) & 0xFF)
		seq_म_लिखो(m, "Chassis component failure! (eg fan or PSU): 0x%.2x\n",
			   (warnreg >> 24) & 0xFF);

	seq_म_लिखो(m, "Battery: %s\n", (warnreg & 0x04) ? "Low!" : "OK");
	seq_म_लिखो(m, "Temp low: %s\n", (warnreg & 0x02) ? "Exceeded!" : "OK");
	seq_म_लिखो(m, "Temp mid: %s\n", (warnreg & 0x01) ? "Exceeded!" : "OK");
	वापस 0;
पूर्ण

अटल पूर्णांक __init pdc_chassis_create_procfs(व्योम)
अणु
	अचिन्हित दीर्घ test;
	पूर्णांक ret;

	ret = pdc_chassis_warn(&test);
	अगर ((ret == PDC_BAD_PROC) || (ret == PDC_BAD_OPTION)) अणु
		/* seems that some boxes (eg L1000) करो not implement this */
		prपूर्णांकk(KERN_INFO "Chassis warnings not supported.\n");
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Enabling PDC chassis warnings support v%s\n",
			PDC_CHASSIS_VER);
	proc_create_single("chassis", 0400, शून्य, pdc_chassis_warn_show);
	वापस 0;
पूर्ण

__initcall(pdc_chassis_create_procfs);

#पूर्ण_अगर /* CONFIG_PROC_FS */
#पूर्ण_अगर /* CONFIG_PDC_CHASSIS_WARN */
