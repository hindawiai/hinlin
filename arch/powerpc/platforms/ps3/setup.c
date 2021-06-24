<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 platक्रमm setup routines.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/console.h>
#समावेश <linux/export.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3gpu.h>

#समावेश "platform.h"

#अगर defined(DEBUG)
#घोषणा DBG udbg_म_लिखो
#अन्यथा
#घोषणा DBG pr_debug
#पूर्ण_अगर

/* mutex synchronizing GPU accesses and video mode changes */
DEFINE_MUTEX(ps3_gpu_mutex);
EXPORT_SYMBOL_GPL(ps3_gpu_mutex);

अटल जोड़ ps3_firmware_version ps3_firmware_version;

व्योम ps3_get_firmware_version(जोड़ ps3_firmware_version *v)
अणु
	*v = ps3_firmware_version;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_get_firmware_version);

पूर्णांक ps3_compare_firmware_version(u16 major, u16 minor, u16 rev)
अणु
	जोड़ ps3_firmware_version x;

	x.pad = 0;
	x.major = major;
	x.minor = minor;
	x.rev = rev;

	वापस (ps3_firmware_version.raw > x.raw) -
	       (ps3_firmware_version.raw < x.raw);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_compare_firmware_version);

अटल व्योम ps3_घातer_save(व्योम)
अणु
	/*
	 * lv1_छोड़ो() माला_दो the PPE thपढ़ो पूर्णांकo inactive state until an
	 * irq on an unmasked plug exists. MSR[EE] has no effect.
	 * flags: 0 = wake on DEC पूर्णांकerrupt, 1 = ignore DEC पूर्णांकerrupt.
	 */

	lv1_छोड़ो(0);
पूर्ण

अटल व्योम __noवापस ps3_restart(अक्षर *cmd)
अणु
	DBG("%s:%d cmd '%s'\n", __func__, __LINE__, cmd);

	smp_send_stop();
	ps3_sys_manager_restart(); /* never वापसs */
पूर्ण

अटल व्योम ps3_घातer_off(व्योम)
अणु
	DBG("%s:%d\n", __func__, __LINE__);

	smp_send_stop();
	ps3_sys_manager_घातer_off(); /* never वापसs */
पूर्ण

अटल व्योम __noवापस ps3_halt(व्योम)
अणु
	DBG("%s:%d\n", __func__, __LINE__);

	smp_send_stop();
	ps3_sys_manager_halt(); /* never वापसs */
पूर्ण

अटल व्योम ps3_panic(अक्षर *str)
अणु
	DBG("%s:%d %s\n", __func__, __LINE__, str);

	smp_send_stop();
	prपूर्णांकk("\n");
	prपूर्णांकk("   System does not reboot automatically.\n");
	prपूर्णांकk("   Please press POWER button.\n");
	prपूर्णांकk("\n");
	panic_flush_kmsg_end();

	जबतक(1)
		lv1_छोड़ो(1);
पूर्ण

#अगर defined(CONFIG_FB_PS3) || defined(CONFIG_FB_PS3_MODULE) || \
    defined(CONFIG_PS3_FLASH) || defined(CONFIG_PS3_FLASH_MODULE)
अटल व्योम __init pपुनः_स्मृति(काष्ठा ps3_pपुनः_स्मृति *p)
अणु
	अगर (!p->size)
		वापस;

	p->address = memblock_alloc(p->size, p->align);
	अगर (!p->address)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, p->size, p->align);

	prपूर्णांकk(KERN_INFO "%s: %lu bytes at %p\n", p->name, p->size,
	       p->address);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FB_PS3) || defined(CONFIG_FB_PS3_MODULE)
काष्ठा ps3_pपुनः_स्मृति ps3fb_videomemory = अणु
	.name = "ps3fb videomemory",
	.size = CONFIG_FB_PS3_DEFAULT_SIZE_M*1024*1024,
	.align = 1024*1024		/* the GPU requires 1 MiB alignment */
पूर्ण;
EXPORT_SYMBOL_GPL(ps3fb_videomemory);
#घोषणा pपुनः_स्मृति_ps3fb_videomemory()	pपुनः_स्मृति(&ps3fb_videomemory)

अटल पूर्णांक __init early_parse_ps3fb(अक्षर *p)
अणु
	अगर (!p)
		वापस 1;

	ps3fb_videomemory.size = ALIGN(memparse(p, &p),
					   ps3fb_videomemory.align);
	वापस 0;
पूर्ण
early_param("ps3fb", early_parse_ps3fb);
#अन्यथा
#घोषणा pपुनः_स्मृति_ps3fb_videomemory()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर defined(CONFIG_PS3_FLASH) || defined(CONFIG_PS3_FLASH_MODULE)
काष्ठा ps3_pपुनः_स्मृति ps3flash_bounce_buffer = अणु
	.name = "ps3flash bounce buffer",
	.size = 256*1024,
	.align = 256*1024
पूर्ण;
EXPORT_SYMBOL_GPL(ps3flash_bounce_buffer);
#घोषणा pपुनः_स्मृति_ps3flash_bounce_buffer()	pपुनः_स्मृति(&ps3flash_bounce_buffer)

अटल पूर्णांक __init early_parse_ps3flash(अक्षर *p)
अणु
	अगर (!p)
		वापस 1;

	अगर (!म_भेद(p, "off"))
		ps3flash_bounce_buffer.size = 0;

	वापस 0;
पूर्ण
early_param("ps3flash", early_parse_ps3flash);
#अन्यथा
#घोषणा pपुनः_स्मृति_ps3flash_bounce_buffer()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक ps3_set_dabr(अचिन्हित दीर्घ dabr, अचिन्हित दीर्घ dabrx)
अणु
	/* Have to set at least one bit in the DABRX */
	अगर (dabrx == 0 && dabr == 0)
		dabrx = DABRX_USER;
	/* hypervisor only allows us to set BTI, Kernel and user */
	dabrx &= DABRX_BTI | DABRX_KERNEL | DABRX_USER;

	वापस lv1_set_dabr(dabr, dabrx) ? -1 : 0;
पूर्ण

अटल व्योम __init ps3_setup_arch(व्योम)
अणु
	u64 पंचांगp;

	DBG(" -> %s:%d\n", __func__, __LINE__);

	lv1_get_version_info(&ps3_firmware_version.raw, &पंचांगp);

	prपूर्णांकk(KERN_INFO "PS3 firmware version %u.%u.%u\n",
	       ps3_firmware_version.major, ps3_firmware_version.minor,
	       ps3_firmware_version.rev);

	ps3_spu_set_platक्रमm();

#अगर_घोषित CONFIG_SMP
	smp_init_ps3();
#पूर्ण_अगर

	pपुनः_स्मृति_ps3fb_videomemory();
	pपुनः_स्मृति_ps3flash_bounce_buffer();

	ppc_md.घातer_save = ps3_घातer_save;
	ps3_os_area_init();

	DBG(" <- %s:%d\n", __func__, __LINE__);
पूर्ण

अटल व्योम __init ps3_progress(अक्षर *s, अचिन्हित लघु hex)
अणु
	prपूर्णांकk("*** %04x : %s\n", hex, s ? s : "");
पूर्ण

व्योम __init ps3_early_mm_init(व्योम)
अणु
	अचिन्हित दीर्घ htab_size;

	ps3_mm_init();
	ps3_mm_vas_create(&htab_size);
	ps3_hpte_init(htab_size);
पूर्ण

अटल पूर्णांक __init ps3_probe(व्योम)
अणु
	DBG(" -> %s:%d\n", __func__, __LINE__);

	अगर (!of_machine_is_compatible("sony,ps3"))
		वापस 0;

	ps3_os_area_save_params();

	pm_घातer_off = ps3_घातer_off;

	DBG(" <- %s:%d\n", __func__, __LINE__);
	वापस 1;
पूर्ण

#अगर defined(CONFIG_KEXEC_CORE)
अटल व्योम ps3_kexec_cpu_करोwn(पूर्णांक crash_shutकरोwn, पूर्णांक secondary)
अणु
	पूर्णांक cpu = smp_processor_id();

	DBG(" -> %s:%d: (%d)\n", __func__, __LINE__, cpu);

	ps3_smp_cleanup_cpu(cpu);
	ps3_shutकरोwn_IRQ(cpu);

	DBG(" <- %s:%d\n", __func__, __LINE__);
पूर्ण
#पूर्ण_अगर

define_machine(ps3) अणु
	.name				= "PS3",
	.probe				= ps3_probe,
	.setup_arch			= ps3_setup_arch,
	.init_IRQ			= ps3_init_IRQ,
	.panic				= ps3_panic,
	.get_boot_समय			= ps3_get_boot_समय,
	.set_dabr			= ps3_set_dabr,
	.calibrate_decr			= ps3_calibrate_decr,
	.progress			= ps3_progress,
	.restart			= ps3_restart,
	.halt				= ps3_halt,
#अगर defined(CONFIG_KEXEC_CORE)
	.kexec_cpu_करोwn			= ps3_kexec_cpu_करोwn,
#पूर्ण_अगर
पूर्ण;
