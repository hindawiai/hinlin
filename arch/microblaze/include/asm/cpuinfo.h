<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generic support क्रम queying CPU info
 *
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <jwilliams@itee.uq.edu.au>
 */

#अगर_अघोषित _ASM_MICROBLAZE_CPUINFO_H
#घोषणा _ASM_MICROBLAZE_CPUINFO_H

#समावेश <linux/of.h>

/* CPU Version and FPGA Family code conversion table type */
काष्ठा cpu_ver_key अणु
	स्थिर अक्षर *s;
	स्थिर अचिन्हित k;
पूर्ण;

बाह्य स्थिर काष्ठा cpu_ver_key cpu_ver_lookup[];

काष्ठा family_string_key अणु
	स्थिर अक्षर *s;
	स्थिर अचिन्हित k;
पूर्ण;

बाह्य स्थिर काष्ठा family_string_key family_string_lookup[];

काष्ठा cpuinfo अणु
	/* Core CPU configuration */
	u32 use_instr;
	u32 use_mult;
	u32 use_fpu;
	u32 use_exc;
	u32 ver_code;
	u32 mmu;
	u32 mmu_privins;
	u32 endian;

	/* CPU caches */
	u32 use_icache;
	u32 icache_tagbits;
	u32 icache_ग_लिखो;
	u32 icache_line_length;
	u32 icache_size;
	अचिन्हित दीर्घ icache_base;
	अचिन्हित दीर्घ icache_high;

	u32 use_dcache;
	u32 dcache_tagbits;
	u32 dcache_ग_लिखो;
	u32 dcache_line_length;
	u32 dcache_size;
	u32 dcache_wb;
	अचिन्हित दीर्घ dcache_base;
	अचिन्हित दीर्घ dcache_high;

	/* Bus connections */
	u32 use_करोpb;
	u32 use_iopb;
	u32 use_dlmb;
	u32 use_ilmb;
	u32 num_fsl;

	/* CPU पूर्णांकerrupt line info */
	u32 irq_edge;
	u32 irq_positive;

	u32 area_optimised;

	/* HW debug support */
	u32 hw_debug;
	u32 num_pc_brk;
	u32 num_rd_brk;
	u32 num_wr_brk;
	u32 cpu_घड़ी_freq; /* store real freq of cpu */

	/* FPGA family */
	u32 fpga_family_code;

	/* User define */
	u32 pvr_user1;
	u32 pvr_user2;
पूर्ण;

बाह्य काष्ठा cpuinfo cpuinfo;

/* fwd declarations of the various CPUinfo populators */
व्योम setup_cpuinfo(व्योम);
व्योम setup_cpuinfo_clk(व्योम);

व्योम set_cpuinfo_अटल(काष्ठा cpuinfo *ci, काष्ठा device_node *cpu);
व्योम set_cpuinfo_pvr_full(काष्ठा cpuinfo *ci, काष्ठा device_node *cpu);

अटल अंतरभूत अचिन्हित पूर्णांक fcpu(काष्ठा device_node *cpu, अक्षर *n)
अणु
	u32 val = 0;

	of_property_पढ़ो_u32(cpu, n, &val);

	वापस val;
पूर्ण

#पूर्ण_अगर /* _ASM_MICROBLAZE_CPUINFO_H */
