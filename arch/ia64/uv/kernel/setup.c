<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI UV Core Functions
 *
 * Copyright (C) 2008 Silicon Graphics, Inc. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>
#समावेश <linux/module.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/uv/uv.h>
#समावेश <यंत्र/uv/uv_mmrs.h>
#समावेश <यंत्र/uv/uv_hub.h>

bool ia64_is_uv;
EXPORT_SYMBOL_GPL(ia64_is_uv);

DEFINE_PER_CPU(काष्ठा uv_hub_info_s, __uv_hub_info);
EXPORT_PER_CPU_SYMBOL_GPL(__uv_hub_info);

काष्ठा redir_addr अणु
	अचिन्हित दीर्घ redirect;
	अचिन्हित दीर्घ alias;
पूर्ण;

#घोषणा DEST_SHIFT UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_0_MMR_DEST_BASE_SHFT

अटल __initdata काष्ठा redir_addr redir_addrs[] = अणु
	अणुUVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_0_MMR, UVH_SI_ALIAS0_OVERLAY_CONFIGपूर्ण,
	अणुUVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_1_MMR, UVH_SI_ALIAS1_OVERLAY_CONFIGपूर्ण,
	अणुUVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_2_MMR, UVH_SI_ALIAS2_OVERLAY_CONFIGपूर्ण,
पूर्ण;

अटल __init व्योम get_lowmem_redirect(अचिन्हित दीर्घ *base, अचिन्हित दीर्घ *size)
अणु
	जोड़ uvh_si_alias0_overlay_config_u alias;
	जोड़ uvh_rh_gam_alias210_redirect_config_2_mmr_u redirect;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(redir_addrs); i++) अणु
		alias.v = uv_पढ़ो_local_mmr(redir_addrs[i].alias);
		अगर (alias.s.base == 0) अणु
			*size = (1UL << alias.s.m_alias);
			redirect.v = uv_पढ़ो_local_mmr(redir_addrs[i].redirect);
			*base = (अचिन्हित दीर्घ)redirect.s.dest_base << DEST_SHIFT;
			वापस;
		पूर्ण
	पूर्ण
	BUG();
पूर्ण

व्योम __init uv_probe_प्रणाली_type(व्योम)
अणु
	काष्ठा acpi_table_rsdp *rsdp;
	काष्ठा acpi_table_xsdt *xsdt;

	अगर (efi.acpi20 == EFI_INVALID_TABLE_ADDR) अणु
		pr_err("ACPI 2.0 RSDP not found.\n");
		वापस;
	पूर्ण

	rsdp = (काष्ठा acpi_table_rsdp *)__va(efi.acpi20);
	अगर (म_भेदन(rsdp->signature, ACPI_SIG_RSDP, माप(ACPI_SIG_RSDP) - 1)) अणु
		pr_err("ACPI 2.0 RSDP signature incorrect.\n");
		वापस;
	पूर्ण

	xsdt = (काष्ठा acpi_table_xsdt *)__va(rsdp->xsdt_physical_address);
	अगर (म_भेदन(xsdt->header.signature, ACPI_SIG_XSDT,
			माप(ACPI_SIG_XSDT) - 1)) अणु
		pr_err("ACPI 2.0 XSDT signature incorrect.\n");
		वापस;
	पूर्ण

	अगर (!म_भेद(xsdt->header.oem_id, "SGI") &&
	    !म_भेद(xsdt->header.oem_table_id + 4, "UV"))
		ia64_is_uv = true;
पूर्ण

व्योम __init uv_setup(अक्षर **cmdline_p)
अणु
	जोड़ uvh_si_addr_map_config_u m_n_config;
	जोड़ uvh_node_id_u node_id;
	अचिन्हित दीर्घ gnode_upper;
	पूर्णांक nid, cpu, m_val, n_val;
	अचिन्हित दीर्घ mmr_base, lowmem_redir_base, lowmem_redir_size;

	get_lowmem_redirect(&lowmem_redir_base, &lowmem_redir_size);
	node_id.v = uv_पढ़ो_local_mmr(UVH_NODE_ID);
	m_n_config.v = uv_पढ़ो_local_mmr(UVH_SI_ADDR_MAP_CONFIG);
	mmr_base = uv_पढ़ो_local_mmr(UVH_RH_GAM_MMR_OVERLAY_CONFIG_MMR) &
			~UV_MMR_ENABLE;

	m_val = m_n_config.s.m_skt;
	n_val = m_n_config.s.n_skt;
	prपूर्णांकk(KERN_DEBUG "UV: global MMR base 0x%lx\n", mmr_base);

	gnode_upper = (((अचिन्हित दीर्घ)node_id.s.node_id) &
		       ~((1 << n_val) - 1)) << m_val;

	क्रम_each_present_cpu(cpu) अणु
		nid = cpu_to_node(cpu);
		uv_cpu_hub_info(cpu)->lowmem_remap_base = lowmem_redir_base;
		uv_cpu_hub_info(cpu)->lowmem_remap_top =
			lowmem_redir_base + lowmem_redir_size;
		uv_cpu_hub_info(cpu)->m_val = m_val;
		uv_cpu_hub_info(cpu)->n_val = n_val;
		uv_cpu_hub_info(cpu)->pnode_mask = (1 << n_val) -1;
		uv_cpu_hub_info(cpu)->gpa_mask = (1 << (m_val + n_val)) - 1;
		uv_cpu_hub_info(cpu)->gnode_upper = gnode_upper;
		uv_cpu_hub_info(cpu)->global_mmr_base = mmr_base;
		uv_cpu_hub_info(cpu)->coherency_करोमुख्य_number = 0;/* ZZZ */
		prपूर्णांकk(KERN_DEBUG "UV cpu %d, nid %d\n", cpu, nid);
	पूर्ण
पूर्ण

