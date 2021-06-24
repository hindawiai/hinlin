<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Dynamic reconfiguration memory support
 *
 * Copyright 2017 IBM Corporation
 */

#घोषणा pr_fmt(fmt) "drmem: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/drस्मृति.स>

अटल पूर्णांक n_root_addr_cells, n_root_size_cells;

अटल काष्ठा drmem_lmb_info __drmem_info;
काष्ठा drmem_lmb_info *drmem_info = &__drmem_info;

u64 drmem_lmb_memory_max(व्योम)
अणु
	काष्ठा drmem_lmb *last_lmb;

	last_lmb = &drmem_info->lmbs[drmem_info->n_lmbs - 1];
	वापस last_lmb->base_addr + drmem_lmb_size();
पूर्ण

अटल u32 drmem_lmb_flags(काष्ठा drmem_lmb *lmb)
अणु
	/*
	 * Return the value of the lmb flags field minus the reserved
	 * bit used पूर्णांकernally क्रम hotplug processing.
	 */
	वापस lmb->flags & ~DRMEM_LMB_RESERVED;
पूर्ण

अटल काष्ठा property *clone_property(काष्ठा property *prop, u32 prop_sz)
अणु
	काष्ठा property *new_prop;

	new_prop = kzalloc(माप(*new_prop), GFP_KERNEL);
	अगर (!new_prop)
		वापस शून्य;

	new_prop->name = kstrdup(prop->name, GFP_KERNEL);
	new_prop->value = kzalloc(prop_sz, GFP_KERNEL);
	अगर (!new_prop->name || !new_prop->value) अणु
		kमुक्त(new_prop->name);
		kमुक्त(new_prop->value);
		kमुक्त(new_prop);
		वापस शून्य;
	पूर्ण

	new_prop->length = prop_sz;
#अगर defined(CONFIG_OF_DYNAMIC)
	of_property_set_flag(new_prop, OF_DYNAMIC);
#पूर्ण_अगर
	वापस new_prop;
पूर्ण

अटल पूर्णांक drmem_update_dt_v1(काष्ठा device_node *memory,
			      काष्ठा property *prop)
अणु
	काष्ठा property *new_prop;
	काष्ठा of_drconf_cell_v1 *dr_cell;
	काष्ठा drmem_lmb *lmb;
	u32 *p;

	new_prop = clone_property(prop, prop->length);
	अगर (!new_prop)
		वापस -1;

	p = new_prop->value;
	*p++ = cpu_to_be32(drmem_info->n_lmbs);

	dr_cell = (काष्ठा of_drconf_cell_v1 *)p;

	क्रम_each_drmem_lmb(lmb) अणु
		dr_cell->base_addr = cpu_to_be64(lmb->base_addr);
		dr_cell->drc_index = cpu_to_be32(lmb->drc_index);
		dr_cell->aa_index = cpu_to_be32(lmb->aa_index);
		dr_cell->flags = cpu_to_be32(drmem_lmb_flags(lmb));

		dr_cell++;
	पूर्ण

	of_update_property(memory, new_prop);
	वापस 0;
पूर्ण

अटल व्योम init_drconf_v2_cell(काष्ठा of_drconf_cell_v2 *dr_cell,
				काष्ठा drmem_lmb *lmb)
अणु
	dr_cell->base_addr = cpu_to_be64(lmb->base_addr);
	dr_cell->drc_index = cpu_to_be32(lmb->drc_index);
	dr_cell->aa_index = cpu_to_be32(lmb->aa_index);
	dr_cell->flags = cpu_to_be32(drmem_lmb_flags(lmb));
पूर्ण

अटल पूर्णांक drmem_update_dt_v2(काष्ठा device_node *memory,
			      काष्ठा property *prop)
अणु
	काष्ठा property *new_prop;
	काष्ठा of_drconf_cell_v2 *dr_cell;
	काष्ठा drmem_lmb *lmb, *prev_lmb;
	u32 lmb_sets, prop_sz, seq_lmbs;
	u32 *p;

	/* First pass, determine how many LMB sets are needed. */
	lmb_sets = 0;
	prev_lmb = शून्य;
	क्रम_each_drmem_lmb(lmb) अणु
		अगर (!prev_lmb) अणु
			prev_lmb = lmb;
			lmb_sets++;
			जारी;
		पूर्ण

		अगर (prev_lmb->aa_index != lmb->aa_index ||
		    drmem_lmb_flags(prev_lmb) != drmem_lmb_flags(lmb))
			lmb_sets++;

		prev_lmb = lmb;
	पूर्ण

	prop_sz = lmb_sets * माप(*dr_cell) + माप(__be32);
	new_prop = clone_property(prop, prop_sz);
	अगर (!new_prop)
		वापस -1;

	p = new_prop->value;
	*p++ = cpu_to_be32(lmb_sets);

	dr_cell = (काष्ठा of_drconf_cell_v2 *)p;

	/* Second pass, populate the LMB set data */
	prev_lmb = शून्य;
	seq_lmbs = 0;
	क्रम_each_drmem_lmb(lmb) अणु
		अगर (prev_lmb == शून्य) अणु
			/* Start of first LMB set */
			prev_lmb = lmb;
			init_drconf_v2_cell(dr_cell, lmb);
			seq_lmbs++;
			जारी;
		पूर्ण

		अगर (prev_lmb->aa_index != lmb->aa_index ||
		    drmem_lmb_flags(prev_lmb) != drmem_lmb_flags(lmb)) अणु
			/* end of one set, start of another */
			dr_cell->seq_lmbs = cpu_to_be32(seq_lmbs);
			dr_cell++;

			init_drconf_v2_cell(dr_cell, lmb);
			seq_lmbs = 1;
		पूर्ण अन्यथा अणु
			seq_lmbs++;
		पूर्ण

		prev_lmb = lmb;
	पूर्ण

	/* बंद out last LMB set */
	dr_cell->seq_lmbs = cpu_to_be32(seq_lmbs);
	of_update_property(memory, new_prop);
	वापस 0;
पूर्ण

पूर्णांक drmem_update_dt(व्योम)
अणु
	काष्ठा device_node *memory;
	काष्ठा property *prop;
	पूर्णांक rc = -1;

	memory = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (!memory)
		वापस -1;

	prop = of_find_property(memory, "ibm,dynamic-memory", शून्य);
	अगर (prop) अणु
		rc = drmem_update_dt_v1(memory, prop);
	पूर्ण अन्यथा अणु
		prop = of_find_property(memory, "ibm,dynamic-memory-v2", शून्य);
		अगर (prop)
			rc = drmem_update_dt_v2(memory, prop);
	पूर्ण

	of_node_put(memory);
	वापस rc;
पूर्ण

अटल व्योम पढ़ो_drconf_v1_cell(काष्ठा drmem_lmb *lmb,
				       स्थिर __be32 **prop)
अणु
	स्थिर __be32 *p = *prop;

	lmb->base_addr = of_पढ़ो_number(p, n_root_addr_cells);
	p += n_root_addr_cells;
	lmb->drc_index = of_पढ़ो_number(p++, 1);

	p++; /* skip reserved field */

	lmb->aa_index = of_पढ़ो_number(p++, 1);
	lmb->flags = of_पढ़ो_number(p++, 1);

	*prop = p;
पूर्ण

अटल पूर्णांक
__walk_drmem_v1_lmbs(स्थिर __be32 *prop, स्थिर __be32 *usm, व्योम *data,
		     पूर्णांक (*func)(काष्ठा drmem_lmb *, स्थिर __be32 **, व्योम *))
अणु
	काष्ठा drmem_lmb lmb;
	u32 i, n_lmbs;
	पूर्णांक ret = 0;

	n_lmbs = of_पढ़ो_number(prop++, 1);
	क्रम (i = 0; i < n_lmbs; i++) अणु
		पढ़ो_drconf_v1_cell(&lmb, &prop);
		ret = func(&lmb, &usm, data);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम पढ़ो_drconf_v2_cell(काष्ठा of_drconf_cell_v2 *dr_cell,
				       स्थिर __be32 **prop)
अणु
	स्थिर __be32 *p = *prop;

	dr_cell->seq_lmbs = of_पढ़ो_number(p++, 1);
	dr_cell->base_addr = of_पढ़ो_number(p, n_root_addr_cells);
	p += n_root_addr_cells;
	dr_cell->drc_index = of_पढ़ो_number(p++, 1);
	dr_cell->aa_index = of_पढ़ो_number(p++, 1);
	dr_cell->flags = of_पढ़ो_number(p++, 1);

	*prop = p;
पूर्ण

अटल पूर्णांक
__walk_drmem_v2_lmbs(स्थिर __be32 *prop, स्थिर __be32 *usm, व्योम *data,
		     पूर्णांक (*func)(काष्ठा drmem_lmb *, स्थिर __be32 **, व्योम *))
अणु
	काष्ठा of_drconf_cell_v2 dr_cell;
	काष्ठा drmem_lmb lmb;
	u32 i, j, lmb_sets;
	पूर्णांक ret = 0;

	lmb_sets = of_पढ़ो_number(prop++, 1);
	क्रम (i = 0; i < lmb_sets; i++) अणु
		पढ़ो_drconf_v2_cell(&dr_cell, &prop);

		क्रम (j = 0; j < dr_cell.seq_lmbs; j++) अणु
			lmb.base_addr = dr_cell.base_addr;
			dr_cell.base_addr += drmem_lmb_size();

			lmb.drc_index = dr_cell.drc_index;
			dr_cell.drc_index++;

			lmb.aa_index = dr_cell.aa_index;
			lmb.flags = dr_cell.flags;

			ret = func(&lmb, &usm, data);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
पूर्णांक __init walk_drmem_lmbs_early(अचिन्हित दीर्घ node, व्योम *data,
		पूर्णांक (*func)(काष्ठा drmem_lmb *, स्थिर __be32 **, व्योम *))
अणु
	स्थिर __be32 *prop, *usm;
	पूर्णांक len, ret = -ENODEV;

	prop = of_get_flat_dt_prop(node, "ibm,lmb-size", &len);
	अगर (!prop || len < dt_root_size_cells * माप(__be32))
		वापस ret;

	/* Get the address & size cells */
	n_root_addr_cells = dt_root_addr_cells;
	n_root_size_cells = dt_root_size_cells;

	drmem_info->lmb_size = dt_mem_next_cell(dt_root_size_cells, &prop);

	usm = of_get_flat_dt_prop(node, "linux,drconf-usable-memory", &len);

	prop = of_get_flat_dt_prop(node, "ibm,dynamic-memory", &len);
	अगर (prop) अणु
		ret = __walk_drmem_v1_lmbs(prop, usm, data, func);
	पूर्ण अन्यथा अणु
		prop = of_get_flat_dt_prop(node, "ibm,dynamic-memory-v2",
					   &len);
		अगर (prop)
			ret = __walk_drmem_v2_lmbs(prop, usm, data, func);
	पूर्ण

	memblock_dump_all();
	वापस ret;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक init_drmem_lmb_size(काष्ठा device_node *dn)
अणु
	स्थिर __be32 *prop;
	पूर्णांक len;

	अगर (drmem_info->lmb_size)
		वापस 0;

	prop = of_get_property(dn, "ibm,lmb-size", &len);
	अगर (!prop || len < n_root_size_cells * माप(__be32)) अणु
		pr_info("Could not determine LMB size\n");
		वापस -1;
	पूर्ण

	drmem_info->lmb_size = of_पढ़ो_number(prop, n_root_size_cells);
	वापस 0;
पूर्ण

/*
 * Returns the property linux,drconf-usable-memory अगर
 * it exists (the property exists only in kexec/kdump kernels,
 * added by kexec-tools)
 */
अटल स्थिर __be32 *of_get_usable_memory(काष्ठा device_node *dn)
अणु
	स्थिर __be32 *prop;
	u32 len;

	prop = of_get_property(dn, "linux,drconf-usable-memory", &len);
	अगर (!prop || len < माप(अचिन्हित पूर्णांक))
		वापस शून्य;

	वापस prop;
पूर्ण

पूर्णांक walk_drmem_lmbs(काष्ठा device_node *dn, व्योम *data,
		    पूर्णांक (*func)(काष्ठा drmem_lmb *, स्थिर __be32 **, व्योम *))
अणु
	स्थिर __be32 *prop, *usm;
	पूर्णांक ret = -ENODEV;

	अगर (!of_root)
		वापस ret;

	/* Get the address & size cells */
	of_node_get(of_root);
	n_root_addr_cells = of_n_addr_cells(of_root);
	n_root_size_cells = of_n_size_cells(of_root);
	of_node_put(of_root);

	अगर (init_drmem_lmb_size(dn))
		वापस ret;

	usm = of_get_usable_memory(dn);

	prop = of_get_property(dn, "ibm,dynamic-memory", शून्य);
	अगर (prop) अणु
		ret = __walk_drmem_v1_lmbs(prop, usm, data, func);
	पूर्ण अन्यथा अणु
		prop = of_get_property(dn, "ibm,dynamic-memory-v2", शून्य);
		अगर (prop)
			ret = __walk_drmem_v2_lmbs(prop, usm, data, func);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __init init_drmem_v1_lmbs(स्थिर __be32 *prop)
अणु
	काष्ठा drmem_lmb *lmb;

	drmem_info->n_lmbs = of_पढ़ो_number(prop++, 1);
	अगर (drmem_info->n_lmbs == 0)
		वापस;

	drmem_info->lmbs = kसुस्मृति(drmem_info->n_lmbs, माप(*lmb),
				   GFP_KERNEL);
	अगर (!drmem_info->lmbs)
		वापस;

	क्रम_each_drmem_lmb(lmb)
		पढ़ो_drconf_v1_cell(lmb, &prop);
पूर्ण

अटल व्योम __init init_drmem_v2_lmbs(स्थिर __be32 *prop)
अणु
	काष्ठा drmem_lmb *lmb;
	काष्ठा of_drconf_cell_v2 dr_cell;
	स्थिर __be32 *p;
	u32 i, j, lmb_sets;
	पूर्णांक lmb_index;

	lmb_sets = of_पढ़ो_number(prop++, 1);
	अगर (lmb_sets == 0)
		वापस;

	/* first pass, calculate the number of LMBs */
	p = prop;
	क्रम (i = 0; i < lmb_sets; i++) अणु
		पढ़ो_drconf_v2_cell(&dr_cell, &p);
		drmem_info->n_lmbs += dr_cell.seq_lmbs;
	पूर्ण

	drmem_info->lmbs = kसुस्मृति(drmem_info->n_lmbs, माप(*lmb),
				   GFP_KERNEL);
	अगर (!drmem_info->lmbs)
		वापस;

	/* second pass, पढ़ो in the LMB inक्रमmation */
	lmb_index = 0;
	p = prop;

	क्रम (i = 0; i < lmb_sets; i++) अणु
		पढ़ो_drconf_v2_cell(&dr_cell, &p);

		क्रम (j = 0; j < dr_cell.seq_lmbs; j++) अणु
			lmb = &drmem_info->lmbs[lmb_index++];

			lmb->base_addr = dr_cell.base_addr;
			dr_cell.base_addr += drmem_info->lmb_size;

			lmb->drc_index = dr_cell.drc_index;
			dr_cell.drc_index++;

			lmb->aa_index = dr_cell.aa_index;
			lmb->flags = dr_cell.flags;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init drmem_init(व्योम)
अणु
	काष्ठा device_node *dn;
	स्थिर __be32 *prop;

	dn = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (!dn) अणु
		pr_info("No dynamic reconfiguration memory found\n");
		वापस 0;
	पूर्ण

	अगर (init_drmem_lmb_size(dn)) अणु
		of_node_put(dn);
		वापस 0;
	पूर्ण

	prop = of_get_property(dn, "ibm,dynamic-memory", शून्य);
	अगर (prop) अणु
		init_drmem_v1_lmbs(prop);
	पूर्ण अन्यथा अणु
		prop = of_get_property(dn, "ibm,dynamic-memory-v2", शून्य);
		अगर (prop)
			init_drmem_v2_lmbs(prop);
	पूर्ण

	of_node_put(dn);
	वापस 0;
पूर्ण
late_initcall(drmem_init);
