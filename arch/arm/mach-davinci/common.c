<शैली गुरु>
/*
 * Code commons to all DaVinci SoCs.
 *
 * Author: Mark A. Greer <mgreer@mvista.com>
 *
 * 2009 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/davinci_emac.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/common.h>
#समावेश <mach/cputype.h>

काष्ठा davinci_soc_info davinci_soc_info;
EXPORT_SYMBOL(davinci_soc_info);

अटल पूर्णांक __init davinci_init_id(काष्ठा davinci_soc_info *soc_info)
अणु
	पूर्णांक			i;
	काष्ठा davinci_id	*dip;
	u8			variant;
	u16			part_no;
	व्योम __iomem		*base;

	base = ioremap(soc_info->jtag_id_reg, SZ_4K);
	अगर (!base) अणु
		pr_err("Unable to map JTAG ID register\n");
		वापस -ENOMEM;
	पूर्ण

	soc_info->jtag_id = __raw_पढ़ोl(base);
	iounmap(base);

	variant = (soc_info->jtag_id & 0xf0000000) >> 28;
	part_no = (soc_info->jtag_id & 0x0ffff000) >> 12;

	क्रम (i = 0, dip = soc_info->ids; i < soc_info->ids_num;
			i++, dip++)
		/* Don't care about the manufacturer right now */
		अगर ((dip->part_no == part_no) && (dip->variant == variant)) अणु
			soc_info->cpu_id = dip->cpu_id;
			pr_info("DaVinci %s variant 0x%x\n", dip->name,
					dip->variant);
			वापस 0;
		पूर्ण

	pr_err("Unknown DaVinci JTAG ID 0x%x\n", soc_info->jtag_id);
	वापस -EINVAL;
पूर्ण

व्योम __init davinci_common_init(स्थिर काष्ठा davinci_soc_info *soc_info)
अणु
	पूर्णांक ret;

	अगर (!soc_info) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	स_नकल(&davinci_soc_info, soc_info, माप(काष्ठा davinci_soc_info));

	अगर (davinci_soc_info.io_desc && (davinci_soc_info.io_desc_num > 0))
		iotable_init(davinci_soc_info.io_desc,
				davinci_soc_info.io_desc_num);

	/*
	 * Normally devicemaps_init() would flush caches and tlb after
	 * mdesc->map_io(), but we must also करो it here because of the CPU
	 * revision check below.
	 */
	local_flush_tlb_all();
	flush_cache_all();

	/*
	 * We want to check CPU revision early क्रम cpu_is_xxxx() macros.
	 * IO space mapping must be initialized beक्रमe we can करो that.
	 */
	ret = davinci_init_id(&davinci_soc_info);
	अगर (ret < 0)
		जाओ err;


	वापस;

err:
	panic("davinci_common_init: SoC Initialization failed\n");
पूर्ण

व्योम __init davinci_init_late(व्योम)
अणु
	davinci_cpufreq_init();
पूर्ण
