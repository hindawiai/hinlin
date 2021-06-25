<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ide.h>

अटल व्योम ide_legacy_init_one(काष्ठा ide_hw **hws, काष्ठा ide_hw *hw,
				u8 port_no, स्थिर काष्ठा ide_port_info *d,
				अचिन्हित दीर्घ config)
अणु
	अचिन्हित दीर्घ base, ctl;
	पूर्णांक irq;

	अगर (port_no == 0) अणु
		base = 0x1f0;
		ctl  = 0x3f6;
		irq  = 14;
	पूर्ण अन्यथा अणु
		base = 0x170;
		ctl  = 0x376;
		irq  = 15;
	पूर्ण

	अगर (!request_region(base, 8, d->name)) अणु
		prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX-0x%lX not free.\n",
				d->name, base, base + 7);
		वापस;
	पूर्ण

	अगर (!request_region(ctl, 1, d->name)) अणु
		prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX not free.\n",
				d->name, ctl);
		release_region(base, 8);
		वापस;
	पूर्ण

	ide_std_init_ports(hw, base, ctl);
	hw->irq = irq;
	hw->config = config;

	hws[port_no] = hw;
पूर्ण

पूर्णांक ide_legacy_device_add(स्थिर काष्ठा ide_port_info *d, अचिन्हित दीर्घ config)
अणु
	काष्ठा ide_hw hw[2], *hws[] = अणु शून्य, शून्य पूर्ण;

	स_रखो(&hw, 0, माप(hw));

	अगर ((d->host_flags & IDE_HFLAG_QD_2ND_PORT) == 0)
		ide_legacy_init_one(hws, &hw[0], 0, d, config);
	ide_legacy_init_one(hws, &hw[1], 1, d, config);

	अगर (hws[0] == शून्य && hws[1] == शून्य &&
	    (d->host_flags & IDE_HFLAG_SINGLE))
		वापस -ENOENT;

	वापस ide_host_add(d, hws, 2, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(ide_legacy_device_add);
