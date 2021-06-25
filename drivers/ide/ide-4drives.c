<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/ide.h>

#घोषणा DRV_NAME "ide-4drives"

अटल bool probe_4drives;

module_param_named(probe, probe_4drives, bool, 0);
MODULE_PARM_DESC(probe, "probe for generic IDE chipset with 4 drives/port");

अटल व्योम ide_4drives_init_dev(ide_drive_t *drive)
अणु
	अगर (drive->hwअगर->channel)
		drive->select ^= 0x20;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops ide_4drives_port_ops = अणु
	.init_dev		= ide_4drives_init_dev,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info ide_4drives_port_info = अणु
	.port_ops		= &ide_4drives_port_ops,
	.host_flags		= IDE_HFLAG_SERIALIZE | IDE_HFLAG_NO_DMA |
				  IDE_HFLAG_4DRIVES,
	.chipset		= ide_4drives,
पूर्ण;

अटल पूर्णांक __init ide_4drives_init(व्योम)
अणु
	अचिन्हित दीर्घ base = 0x1f0, ctl = 0x3f6;
	काष्ठा ide_hw hw, *hws[] = अणु &hw, &hw पूर्ण;

	अगर (probe_4drives == 0)
		वापस -ENODEV;

	अगर (!request_region(base, 8, DRV_NAME)) अणु
		prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX-0x%lX not free.\n",
				DRV_NAME, base, base + 7);
		वापस -EBUSY;
	पूर्ण

	अगर (!request_region(ctl, 1, DRV_NAME)) अणु
		prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX not free.\n",
				DRV_NAME, ctl);
		release_region(base, 8);
		वापस -EBUSY;
	पूर्ण

	स_रखो(&hw, 0, माप(hw));

	ide_std_init_ports(&hw, base, ctl);
	hw.irq = 14;

	वापस ide_host_add(&ide_4drives_port_info, hws, 2, शून्य);
पूर्ण

module_init(ide_4drives_init);

MODULE_AUTHOR("Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("generic IDE chipset with 4 drives/port support");
MODULE_LICENSE("GPL");
