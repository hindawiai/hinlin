<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम Esteem 195E Hotfoot CPU Board
 *
 * Author: Solomon Peachy <solomon@linux-wlan.com>
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "reg.h"
#समावेश "dcr.h"
#समावेश "4xx.h"
#समावेश "cuboot.h"

#घोषणा TARGET_4xx
#घोषणा TARGET_HOTFOOT

#समावेश "ppcboot-hotfoot.h"

अटल bd_t bd;

#घोषणा NUM_REGS 3

अटल व्योम hotfoot_fixups(व्योम)
अणु
	u32 uart = mfdcr(DCRN_CPC0_UCR) & 0x7f;

	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize); 

	dt_fixup_cpu_घड़ीs(bd.bi_procfreq, bd.bi_procfreq, 0);
	dt_fixup_घड़ी("/plb", bd.bi_plb_busfreq);
	dt_fixup_घड़ी("/plb/opb", bd.bi_opbfreq);
	dt_fixup_घड़ी("/plb/ebc", bd.bi_pci_busfreq);
	dt_fixup_घड़ी("/plb/opb/serial@ef600300", bd.bi_procfreq / uart); 
	dt_fixup_घड़ी("/plb/opb/serial@ef600400", bd.bi_procfreq / uart); 
	
	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
	dt_fixup_mac_address_by_alias("ethernet1", bd.bi_enet1addr);

	/* Is this a single eth/serial board? */
	अगर ((bd.bi_enet1addr[0] == 0) && 
	    (bd.bi_enet1addr[1] == 0) &&
	    (bd.bi_enet1addr[2] == 0) &&
	    (bd.bi_enet1addr[3] == 0) &&
	    (bd.bi_enet1addr[4] == 0) &&
	    (bd.bi_enet1addr[5] == 0)) अणु
		व्योम *devp;

		म_लिखो("Trimming devtree for single serial/eth board\n");

		devp = finddevice("/plb/opb/serial@ef600300");
		अगर (!devp)
			fatal("Can't find node for /plb/opb/serial@ef600300");
		del_node(devp);

		devp = finddevice("/plb/opb/ethernet@ef600900");
		अगर (!devp)
			fatal("Can't find node for /plb/opb/ethernet@ef600900");
		del_node(devp);
	पूर्ण

	ibm4xx_quiesce_eth((u32 *)0xef600800, (u32 *)0xef600900);

	/* Fix up flash size in fdt क्रम 4M boards. */
	अगर (bd.bi_flashsize < 0x800000) अणु
		u32 regs[NUM_REGS];
		व्योम *devp = finddevice("/plb/ebc/nor_flash@0");
		अगर (!devp)
			fatal("Can't find FDT node for nor_flash!??");

		म_लिखो("Fixing devtree for 4M Flash\n");
		
		/* First fix up the base addresse */
		getprop(devp, "reg", regs, माप(regs));
		regs[0] = 0;
		regs[1] = 0xffc00000;
		regs[2] = 0x00400000;
		setprop(devp, "reg", regs, माप(regs));
		
		/* Then the offsets */
		devp = finddevice("/plb/ebc/nor_flash@0/partition@0");
		अगर (!devp)
			fatal("Can't find FDT node for partition@0");
		getprop(devp, "reg", regs, 2*माप(u32));
		regs[0] -= 0x400000;
		setprop(devp, "reg", regs,  2*माप(u32));

		devp = finddevice("/plb/ebc/nor_flash@0/partition@1");
		अगर (!devp)
			fatal("Can't find FDT node for partition@1");
		getprop(devp, "reg", regs, 2*माप(u32));
		regs[0] -= 0x400000;
		setprop(devp, "reg", regs,  2*माप(u32));

		devp = finddevice("/plb/ebc/nor_flash@0/partition@2");
		अगर (!devp)
			fatal("Can't find FDT node for partition@2");
		getprop(devp, "reg", regs, 2*माप(u32));
		regs[0] -= 0x400000;
		setprop(devp, "reg", regs,  2*माप(u32));

		devp = finddevice("/plb/ebc/nor_flash@0/partition@3");
		अगर (!devp)
			fatal("Can't find FDT node for partition@3");
		getprop(devp, "reg", regs, 2*माप(u32));
		regs[0] -= 0x400000;
		setprop(devp, "reg", regs,  2*माप(u32));

		devp = finddevice("/plb/ebc/nor_flash@0/partition@4");
		अगर (!devp)
			fatal("Can't find FDT node for partition@4");
		getprop(devp, "reg", regs, 2*माप(u32));
		regs[0] -= 0x400000;
		setprop(devp, "reg", regs,  2*माप(u32));

		devp = finddevice("/plb/ebc/nor_flash@0/partition@6");
		अगर (!devp)
			fatal("Can't find FDT node for partition@6");
		getprop(devp, "reg", regs, 2*माप(u32));
		regs[0] -= 0x400000;
		setprop(devp, "reg", regs,  2*माप(u32));

		/* Delete the FeatFS node */
		devp = finddevice("/plb/ebc/nor_flash@0/partition@5");
		अगर (!devp)
			fatal("Can't find FDT node for partition@5");
		del_node(devp);
	पूर्ण
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	platक्रमm_ops.fixups = hotfoot_fixups;
        platक्रमm_ops.निकास = ibm40x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
