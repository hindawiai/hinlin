<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FSL SoC setup code
 *
 * Maपूर्णांकained by Kumar Gala (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * 2006 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/major.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/export.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/fs_enet_pd.h>
#समावेश <linux/fs_uart_pd.h>
#समावेश <linux/reboot.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/cpm2.h>
#समावेश <यंत्र/fsl_hcalls.h>	/* For the Freescale hypervisor */

बाह्य व्योम init_fcc_ioports(काष्ठा fs_platक्रमm_info*);
बाह्य व्योम init_fec_ioports(काष्ठा fs_platक्रमm_info*);
बाह्य व्योम init_smc_ioports(काष्ठा fs_uart_platक्रमm_info*);
अटल phys_addr_t immrbase = -1;

phys_addr_t get_immrbase(व्योम)
अणु
	काष्ठा device_node *soc;

	अगर (immrbase != -1)
		वापस immrbase;

	soc = of_find_node_by_type(शून्य, "soc");
	अगर (soc) अणु
		पूर्णांक size;
		u32 naddr;
		स्थिर __be32 *prop = of_get_property(soc, "#address-cells", &size);

		अगर (prop && size == 4)
			naddr = be32_to_cpup(prop);
		अन्यथा
			naddr = 2;

		prop = of_get_property(soc, "ranges", &size);
		अगर (prop)
			immrbase = of_translate_address(soc, prop + naddr);

		of_node_put(soc);
	पूर्ण

	वापस immrbase;
पूर्ण

EXPORT_SYMBOL(get_immrbase);

u32 fsl_get_sys_freq(व्योम)
अणु
	अटल u32 sysfreq = -1;
	काष्ठा device_node *soc;

	अगर (sysfreq != -1)
		वापस sysfreq;

	soc = of_find_node_by_type(शून्य, "soc");
	अगर (!soc)
		वापस -1;

	of_property_पढ़ो_u32(soc, "clock-frequency", &sysfreq);
	अगर (sysfreq == -1 || !sysfreq)
		of_property_पढ़ो_u32(soc, "bus-frequency", &sysfreq);

	of_node_put(soc);
	वापस sysfreq;
पूर्ण
EXPORT_SYMBOL(fsl_get_sys_freq);

#अगर defined(CONFIG_CPM) || defined(CONFIG_QUICC_ENGINE)

u32 get_brgfreq(व्योम)
अणु
	अटल u32 brgfreq = -1;
	काष्ठा device_node *node;

	अगर (brgfreq != -1)
		वापस brgfreq;

	node = of_find_compatible_node(शून्य, शून्य, "fsl,cpm-brg");
	अगर (node) अणु
		of_property_पढ़ो_u32(node, "clock-frequency", &brgfreq);
		of_node_put(node);
		वापस brgfreq;
	पूर्ण

	/* Legacy device binding -- will go away when no users are left. */
	node = of_find_node_by_type(शून्य, "cpm");
	अगर (!node)
		node = of_find_compatible_node(शून्य, शून्य, "fsl,qe");
	अगर (!node)
		node = of_find_node_by_type(शून्य, "qe");

	अगर (node) अणु
		of_property_पढ़ो_u32(node, "brg-frequency", &brgfreq);
		अगर (brgfreq == -1 || !brgfreq)
			अगर (!of_property_पढ़ो_u32(node, "bus-frequency",
						  &brgfreq))
				brgfreq /= 2;
		of_node_put(node);
	पूर्ण

	वापस brgfreq;
पूर्ण

EXPORT_SYMBOL(get_brgfreq);

u32 get_baudrate(व्योम)
अणु
	अटल u32 fs_baudrate = -1;
	काष्ठा device_node *node;

	अगर (fs_baudrate != -1)
		वापस fs_baudrate;

	node = of_find_node_by_type(शून्य, "serial");
	अगर (node) अणु
		of_property_पढ़ो_u32(node, "current-speed", &fs_baudrate);
		of_node_put(node);
	पूर्ण

	वापस fs_baudrate;
पूर्ण

EXPORT_SYMBOL(get_baudrate);
#पूर्ण_अगर /* CONFIG_CPM2 */

#अगर defined(CONFIG_FSL_SOC_BOOKE) || defined(CONFIG_PPC_86xx)
अटल __be32 __iomem *rstcr;

अटल पूर्णांक fsl_rstcr_restart(काष्ठा notअगरier_block *this,
			     अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	local_irq_disable();
	/* set reset control रेजिस्टर */
	out_be32(rstcr, 0x2);	/* HRESET_REQ */

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक __init setup_rstcr(व्योम)
अणु
	काष्ठा device_node *np;

	अटल काष्ठा notअगरier_block restart_handler = अणु
		.notअगरier_call = fsl_rstcr_restart,
		.priority = 128,
	पूर्ण;

	क्रम_each_node_by_name(np, "global-utilities") अणु
		अगर ((of_get_property(np, "fsl,has-rstcr", शून्य))) अणु
			rstcr = of_iomap(np, 0) + 0xb0;
			अगर (!rstcr) अणु
				prपूर्णांकk (KERN_ERR "Error: reset control "
						"register not mapped!\n");
			पूर्ण अन्यथा अणु
				रेजिस्टर_restart_handler(&restart_handler);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(np);

	वापस 0;
पूर्ण

arch_initcall(setup_rstcr);

#पूर्ण_अगर

#अगर defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)
काष्ठा platक्रमm_diu_data_ops diu_ops;
EXPORT_SYMBOL(diu_ops);
#पूर्ण_अगर

#अगर_घोषित CONFIG_EPAPR_PARAVIRT
/*
 * Restart the current partition
 *
 * This function should be asचिन्हित to the ppc_md.restart function poपूर्णांकer,
 * to initiate a partition restart when we're running under the Freescale
 * hypervisor.
 */
व्योम __noवापस fsl_hv_restart(अक्षर *cmd)
अणु
	pr_info("hv restart\n");
	fh_partition_restart(-1);
	जबतक (1) ;
पूर्ण

/*
 * Halt the current partition
 *
 * This function should be asचिन्हित to the pm_घातer_off and ppc_md.halt
 * function poपूर्णांकers, to shut करोwn the partition when we're running under
 * the Freescale hypervisor.
 */
व्योम __noवापस fsl_hv_halt(व्योम)
अणु
	pr_info("hv exit\n");
	fh_partition_stop(-1);
	जबतक (1) ;
पूर्ण
#पूर्ण_अगर
