<शैली गुरु>
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/pvr.h>

अटल स्थिर अक्षर family_string[] = CONFIG_XILINX_MICROBLAZE0_FAMILY;
अटल स्थिर अक्षर cpu_ver_string[] = CONFIG_XILINX_MICROBLAZE0_HW_VER;

#घोषणा err_prपूर्णांकk(x) \
	early_prपूर्णांकk("ERROR: Microblaze " x "-different for kernel and DTS\n");

व्योम __init set_cpuinfo_अटल(काष्ठा cpuinfo *ci, काष्ठा device_node *cpu)
अणु
	u32 i = 0;

	ci->use_instr =
		(fcpu(cpu, "xlnx,use-barrel") ? PVR0_USE_BARREL_MASK : 0) |
		(fcpu(cpu, "xlnx,use-msr-instr") ? PVR2_USE_MSR_INSTR : 0) |
		(fcpu(cpu, "xlnx,use-pcmp-instr") ? PVR2_USE_PCMP_INSTR : 0) |
		(fcpu(cpu, "xlnx,use-div") ? PVR0_USE_DIV_MASK : 0);
	अगर (CONFIG_XILINX_MICROBLAZE0_USE_BARREL)
		i |= PVR0_USE_BARREL_MASK;
	अगर (CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR)
		i |= PVR2_USE_MSR_INSTR;
	अगर (CONFIG_XILINX_MICROBLAZE0_USE_PCMP_INSTR)
		i |= PVR2_USE_PCMP_INSTR;
	अगर (CONFIG_XILINX_MICROBLAZE0_USE_DIV)
		i |= PVR0_USE_DIV_MASK;
	अगर (ci->use_instr != i)
		err_prपूर्णांकk("BARREL, MSR, PCMP or DIV");

	ci->use_mult = fcpu(cpu, "xlnx,use-hw-mul");
	अगर (ci->use_mult != CONFIG_XILINX_MICROBLAZE0_USE_HW_MUL)
		err_prपूर्णांकk("HW_MUL");
	ci->use_mult =
		(ci->use_mult > 1 ?
				(PVR2_USE_MUL64_MASK | PVR0_USE_HW_MUL_MASK) :
				(ci->use_mult == 1 ? PVR0_USE_HW_MUL_MASK : 0));

	ci->use_fpu = fcpu(cpu, "xlnx,use-fpu");
	अगर (ci->use_fpu != CONFIG_XILINX_MICROBLAZE0_USE_FPU)
		err_prपूर्णांकk("HW_FPU");
	ci->use_fpu = (ci->use_fpu > 1 ?
				(PVR2_USE_FPU2_MASK | PVR0_USE_FPU_MASK) :
				(ci->use_fpu == 1 ? PVR0_USE_FPU_MASK : 0));

	ci->use_exc =
		(fcpu(cpu, "xlnx,unaligned-exceptions") ?
				PVR2_UNALIGNED_EXC_MASK : 0) |
		(fcpu(cpu, "xlnx,ill-opcode-exception") ?
				PVR2_ILL_OPCODE_EXC_MASK : 0) |
		(fcpu(cpu, "xlnx,iopb-bus-exception") ?
				PVR2_IOPB_BUS_EXC_MASK : 0) |
		(fcpu(cpu, "xlnx,dopb-bus-exception") ?
				PVR2_DOPB_BUS_EXC_MASK : 0) |
		(fcpu(cpu, "xlnx,div-zero-exception") ?
				PVR2_DIV_ZERO_EXC_MASK : 0) |
		(fcpu(cpu, "xlnx,fpu-exception") ? PVR2_FPU_EXC_MASK : 0) |
		(fcpu(cpu, "xlnx,fsl-exception") ? PVR2_USE_EXTEND_FSL : 0);

	ci->use_icache = fcpu(cpu, "xlnx,use-icache");
	ci->icache_tagbits = fcpu(cpu, "xlnx,addr-tag-bits");
	ci->icache_ग_लिखो = fcpu(cpu, "xlnx,allow-icache-wr");
	ci->icache_line_length = fcpu(cpu, "xlnx,icache-line-len") << 2;
	अगर (!ci->icache_line_length) अणु
		अगर (fcpu(cpu, "xlnx,icache-use-fsl"))
			ci->icache_line_length = 4 << 2;
		अन्यथा
			ci->icache_line_length = 1 << 2;
	पूर्ण
	ci->icache_size = fcpu(cpu, "i-cache-size");
	ci->icache_base = fcpu(cpu, "i-cache-baseaddr");
	ci->icache_high = fcpu(cpu, "i-cache-highaddr");

	ci->use_dcache = fcpu(cpu, "xlnx,use-dcache");
	ci->dcache_tagbits = fcpu(cpu, "xlnx,dcache-addr-tag");
	ci->dcache_ग_लिखो = fcpu(cpu, "xlnx,allow-dcache-wr");
	ci->dcache_line_length = fcpu(cpu, "xlnx,dcache-line-len") << 2;
	अगर (!ci->dcache_line_length) अणु
		अगर (fcpu(cpu, "xlnx,dcache-use-fsl"))
			ci->dcache_line_length = 4 << 2;
		अन्यथा
			ci->dcache_line_length = 1 << 2;
	पूर्ण
	ci->dcache_size = fcpu(cpu, "d-cache-size");
	ci->dcache_base = fcpu(cpu, "d-cache-baseaddr");
	ci->dcache_high = fcpu(cpu, "d-cache-highaddr");
	ci->dcache_wb = fcpu(cpu, "xlnx,dcache-use-writeback");

	ci->use_करोpb = fcpu(cpu, "xlnx,d-opb");
	ci->use_iopb = fcpu(cpu, "xlnx,i-opb");
	ci->use_dlmb = fcpu(cpu, "xlnx,d-lmb");
	ci->use_ilmb = fcpu(cpu, "xlnx,i-lmb");

	ci->num_fsl = fcpu(cpu, "xlnx,fsl-links");
	ci->irq_edge = fcpu(cpu, "xlnx,interrupt-is-edge");
	ci->irq_positive = fcpu(cpu, "xlnx,edge-is-positive");
	ci->area_optimised = 0;

	ci->hw_debug = fcpu(cpu, "xlnx,debug-enabled");
	ci->num_pc_brk = fcpu(cpu, "xlnx,number-of-pc-brk");
	ci->num_rd_brk = fcpu(cpu, "xlnx,number-of-rd-addr-brk");
	ci->num_wr_brk = fcpu(cpu, "xlnx,number-of-wr-addr-brk");

	ci->pvr_user1 = fcpu(cpu, "xlnx,pvr-user1");
	ci->pvr_user2 = fcpu(cpu, "xlnx,pvr-user2");

	ci->mmu = fcpu(cpu, "xlnx,use-mmu");
	ci->mmu_privins = fcpu(cpu, "xlnx,mmu-privileged-instr");
	ci->endian = fcpu(cpu, "xlnx,endianness");

	ci->ver_code = 0;
	ci->fpga_family_code = 0;

	/* Do various fixups based on CPU version and FPGA family strings */

	/* Resolved the CPU version code */
	क्रम (i = 0; cpu_ver_lookup[i].s != शून्य; i++) अणु
		अगर (म_भेद(cpu_ver_lookup[i].s, cpu_ver_string) == 0)
			ci->ver_code = cpu_ver_lookup[i].k;
	पूर्ण

	/* Resolved the fpga family code */
	क्रम (i = 0; family_string_lookup[i].s != शून्य; i++) अणु
		अगर (म_भेद(family_string_lookup[i].s, family_string) == 0)
			ci->fpga_family_code = family_string_lookup[i].k;
	पूर्ण

	/* FIXME - mb3 and spartan2 करो not exist in PVR */
	/* This is mb3 and on a non Spartan2 */
	अगर (ci->ver_code == 0x20 && ci->fpga_family_code != 0xf0)
		/* Hardware Multiplier in use */
		ci->use_mult = 1;
पूर्ण
