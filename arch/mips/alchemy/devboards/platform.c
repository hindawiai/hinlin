<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * devoard misc stuff.
 */

#समावेश <linux/init.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>

#समावेश <prom.h>

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	अगर (alchemy_get_cputype() == ALCHEMY_CPU_AU1300)
		alchemy_uart_अक्षर_दो(AU1300_UART2_PHYS_ADDR, c);
	अन्यथा
		alchemy_uart_अक्षर_दो(AU1000_UART0_PHYS_ADDR, c);
पूर्ण


अटल काष्ठा platक्रमm_device db1x00_rtc_dev = अणु
	.name	= "rtc-au1xxx",
	.id	= -1,
पूर्ण;


अटल व्योम db1x_घातer_off(व्योम)
अणु
	bcsr_ग_लिखो(BCSR_RESETS, 0);
	bcsr_ग_लिखो(BCSR_SYSTEM, BCSR_SYSTEM_PWROFF | BCSR_SYSTEM_RESET);
	जबतक (1)		/* sit and spin */
		cpu_रुको();
पूर्ण

अटल व्योम db1x_reset(अक्षर *c)
अणु
	bcsr_ग_लिखो(BCSR_RESETS, 0);
	bcsr_ग_लिखो(BCSR_SYSTEM, 0);
पूर्ण

अटल पूर्णांक __init db1x_late_setup(व्योम)
अणु
	अगर (!pm_घातer_off)
		pm_घातer_off = db1x_घातer_off;
	अगर (!_machine_halt)
		_machine_halt = db1x_घातer_off;
	अगर (!_machine_restart)
		_machine_restart = db1x_reset;

	platक्रमm_device_रेजिस्टर(&db1x00_rtc_dev);

	वापस 0;
पूर्ण
device_initcall(db1x_late_setup);

/* रेजिस्टर a pcmcia socket */
पूर्णांक __init db1x_रेजिस्टर_pcmcia_socket(phys_addr_t pcmcia_attr_start,
				       phys_addr_t pcmcia_attr_end,
				       phys_addr_t pcmcia_mem_start,
				       phys_addr_t pcmcia_mem_end,
				       phys_addr_t pcmcia_io_start,
				       phys_addr_t pcmcia_io_end,
				       पूर्णांक card_irq,
				       पूर्णांक cd_irq,
				       पूर्णांक stschg_irq,
				       पूर्णांक eject_irq,
				       पूर्णांक id)
अणु
	पूर्णांक cnt, i, ret;
	काष्ठा resource *sr;
	काष्ठा platक्रमm_device *pd;

	cnt = 5;
	अगर (eject_irq)
		cnt++;
	अगर (stschg_irq)
		cnt++;

	sr = kसुस्मृति(cnt, माप(काष्ठा resource), GFP_KERNEL);
	अगर (!sr)
		वापस -ENOMEM;

	pd = platक्रमm_device_alloc("db1xxx_pcmcia", id);
	अगर (!pd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	sr[0].name	= "pcmcia-attr";
	sr[0].flags	= IORESOURCE_MEM;
	sr[0].start	= pcmcia_attr_start;
	sr[0].end	= pcmcia_attr_end;

	sr[1].name	= "pcmcia-mem";
	sr[1].flags	= IORESOURCE_MEM;
	sr[1].start	= pcmcia_mem_start;
	sr[1].end	= pcmcia_mem_end;

	sr[2].name	= "pcmcia-io";
	sr[2].flags	= IORESOURCE_MEM;
	sr[2].start	= pcmcia_io_start;
	sr[2].end	= pcmcia_io_end;

	sr[3].name	= "insert";
	sr[3].flags	= IORESOURCE_IRQ;
	sr[3].start = sr[3].end = cd_irq;

	sr[4].name	= "card";
	sr[4].flags	= IORESOURCE_IRQ;
	sr[4].start = sr[4].end = card_irq;

	i = 5;
	अगर (stschg_irq) अणु
		sr[i].name	= "stschg";
		sr[i].flags	= IORESOURCE_IRQ;
		sr[i].start = sr[i].end = stschg_irq;
		i++;
	पूर्ण
	अगर (eject_irq) अणु
		sr[i].name	= "eject";
		sr[i].flags	= IORESOURCE_IRQ;
		sr[i].start = sr[i].end = eject_irq;
	पूर्ण

	pd->resource = sr;
	pd->num_resources = cnt;

	ret = platक्रमm_device_add(pd);
	अगर (!ret)
		वापस 0;

	platक्रमm_device_put(pd);
out:
	kमुक्त(sr);
	वापस ret;
पूर्ण

#घोषणा YAMON_SIZE	0x00100000
#घोषणा YAMON_ENV_SIZE	0x00040000

पूर्णांक __init db1x_रेजिस्टर_norflash(अचिन्हित दीर्घ size, पूर्णांक width,
				  पूर्णांक swapped)
अणु
	काष्ठा physmap_flash_data *pfd;
	काष्ठा platक्रमm_device *pd;
	काष्ठा mtd_partition *parts;
	काष्ठा resource *res;
	पूर्णांक ret, i;

	अगर (size < (8 * 1024 * 1024))
		वापस -EINVAL;

	ret = -ENOMEM;
	parts = kसुस्मृति(5, माप(काष्ठा mtd_partition), GFP_KERNEL);
	अगर (!parts)
		जाओ out;

	res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	अगर (!res)
		जाओ out1;

	pfd = kzalloc(माप(काष्ठा physmap_flash_data), GFP_KERNEL);
	अगर (!pfd)
		जाओ out2;

	pd = platक्रमm_device_alloc("physmap-flash", 0);
	अगर (!pd)
		जाओ out3;

	/* NOR flash ends at 0x20000000, regardless of size */
	res->start = 0x20000000 - size;
	res->end = 0x20000000 - 1;
	res->flags = IORESOURCE_MEM;

	/* partition setup.  Most Develboards have a चयन which allows
	 * to swap the physical locations of the 2 NOR flash banks.
	 */
	i = 0;
	अगर (!swapped) अणु
		/* first NOR chip */
		parts[i].offset = 0;
		parts[i].name = "User FS";
		parts[i].size = size / 2;
		i++;
	पूर्ण

	parts[i].offset = MTDPART_OFS_APPEND;
	parts[i].name = "User FS 2";
	parts[i].size = (size / 2) - (0x20000000 - 0x1fc00000);
	i++;

	parts[i].offset = MTDPART_OFS_APPEND;
	parts[i].name = "YAMON";
	parts[i].size = YAMON_SIZE;
	parts[i].mask_flags = MTD_WRITEABLE;
	i++;

	parts[i].offset = MTDPART_OFS_APPEND;
	parts[i].name = "raw kernel";
	parts[i].size = 0x00400000 - YAMON_SIZE - YAMON_ENV_SIZE;
	i++;

	parts[i].offset = MTDPART_OFS_APPEND;
	parts[i].name = "YAMON Env";
	parts[i].size = YAMON_ENV_SIZE;
	parts[i].mask_flags = MTD_WRITEABLE;
	i++;

	अगर (swapped) अणु
		parts[i].offset = MTDPART_OFS_APPEND;
		parts[i].name = "User FS";
		parts[i].size = size / 2;
		i++;
	पूर्ण

	pfd->width = width;
	pfd->parts = parts;
	pfd->nr_parts = 5;

	pd->dev.platक्रमm_data = pfd;
	pd->resource = res;
	pd->num_resources = 1;

	ret = platक्रमm_device_add(pd);
	अगर (!ret)
		वापस ret;

	platक्रमm_device_put(pd);
out3:
	kमुक्त(pfd);
out2:
	kमुक्त(res);
out1:
	kमुक्त(parts);
out:
	वापस ret;
पूर्ण
