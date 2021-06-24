<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Author: Alexander Shiyan <shc_work@mail.ru>, 2016
 */

#समावेश <linux/पन.स>
#समावेश <linux/of_fdt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sizes.h>

#समावेश <linux/mfd/syscon/clps711x.h>

#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#घोषणा CLPS711X_VIRT_BASE	IOMEM(0xfeff4000)
#घोषणा CLPS711X_PHYS_BASE	(0x80000000)
# define SYSFLG1		(0x0140)
# define HALT			(0x0800)
# define UNIQID			(0x2440)
# define RANDID0		(0x2700)
# define RANDID1		(0x2704)
# define RANDID2		(0x2708)
# define RANDID3		(0x270c)

अटल काष्ठा map_desc clps711x_io_desc __initdata = अणु
	.भव	= (अचिन्हित दीर्घ)CLPS711X_VIRT_BASE,
	.pfn		= __phys_to_pfn(CLPS711X_PHYS_BASE),
	.length		= 48 * SZ_1K,
	.type		= MT_DEVICE,
पूर्ण;

अटल व्योम __init clps711x_map_io(व्योम)
अणु
	iotable_init(&clps711x_io_desc, 1);
पूर्ण

अटल स्थिर काष्ठा resource clps711x_cpuidle_res =
	DEFINE_RES_MEM(CLPS711X_PHYS_BASE + HALT, SZ_128);

अटल व्योम __init clps711x_init(व्योम)
अणु
	u32 id[5];

	id[0] = पढ़ोl(CLPS711X_VIRT_BASE + UNIQID);
	id[1] = पढ़ोl(CLPS711X_VIRT_BASE + RANDID0);
	id[2] = पढ़ोl(CLPS711X_VIRT_BASE + RANDID1);
	id[3] = पढ़ोl(CLPS711X_VIRT_BASE + RANDID2);
	id[4] = पढ़ोl(CLPS711X_VIRT_BASE + RANDID3);
	प्रणाली_rev = SYSFLG1_VERID(पढ़ोl(CLPS711X_VIRT_BASE + SYSFLG1));

	add_device_अक्रमomness(id, माप(id));

	प्रणाली_serial_low = id[0];

	platक्रमm_device_रेजिस्टर_simple("clps711x-cpuidle", PLATFORM_DEVID_NONE,
					&clps711x_cpuidle_res, 1);
पूर्ण

अटल व्योम clps711x_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	soft_restart(0);
पूर्ण

अटल स्थिर अक्षर *स्थिर clps711x_compat[] __initस्थिर = अणु
	"cirrus,ep7209",
	शून्य
पूर्ण;

DT_MACHINE_START(CLPS711X_DT, "Cirrus Logic CLPS711X (Device Tree Support)")
	.dt_compat	= clps711x_compat,
	.map_io		= clps711x_map_io,
	.init_late	= clps711x_init,
	.restart	= clps711x_restart,
MACHINE_END
