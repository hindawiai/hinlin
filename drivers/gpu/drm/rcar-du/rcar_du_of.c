<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rcar_du_of.c - Legacy DT bindings compatibility
 *
 * Copyright (C) 2018 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *
 * Based on work from Jyri Sarha <jsarha@ti.com>
 * Copyright (C) 2015 Texas Instruments
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/slab.h>

#समावेश "rcar_du_crtc.h"
#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_of.h"

/* -----------------------------------------------------------------------------
 * Generic Overlay Handling
 */

काष्ठा rcar_du_of_overlay अणु
	स्थिर अक्षर *compatible;
	व्योम *begin;
	व्योम *end;
पूर्ण;

#घोषणा RCAR_DU_OF_DTB(type, soc)					\
	बाह्य अक्षर __dtb_rcar_du_of_##type##_##soc##_begin[];		\
	बाह्य अक्षर __dtb_rcar_du_of_##type##_##soc##_end[]

#घोषणा RCAR_DU_OF_OVERLAY(type, soc)					\
	अणु								\
		.compatible = "renesas,du-" #soc,			\
		.begin = __dtb_rcar_du_of_##type##_##soc##_begin,	\
		.end = __dtb_rcar_du_of_##type##_##soc##_end,		\
	पूर्ण

अटल पूर्णांक __init rcar_du_of_apply_overlay(स्थिर काष्ठा rcar_du_of_overlay *dtbs,
					   स्थिर अक्षर *compatible)
अणु
	स्थिर काष्ठा rcar_du_of_overlay *dtb = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक ovcs_id;

	क्रम (i = 0; dtbs[i].compatible; ++i) अणु
		अगर (!म_भेद(dtbs[i].compatible, compatible)) अणु
			dtb = &dtbs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!dtb)
		वापस -ENODEV;

	ovcs_id = 0;
	वापस of_overlay_fdt_apply(dtb->begin, dtb->end - dtb->begin,
				    &ovcs_id);
पूर्ण

अटल पूर्णांक __init rcar_du_of_add_property(काष्ठा of_changeset *ocs,
					  काष्ठा device_node *np,
					  स्थिर अक्षर *name, स्थिर व्योम *value,
					  पूर्णांक length)
अणु
	काष्ठा property *prop;
	पूर्णांक ret = -ENOMEM;

	prop = kzalloc(माप(*prop), GFP_KERNEL);
	अगर (!prop)
		वापस -ENOMEM;

	prop->name = kstrdup(name, GFP_KERNEL);
	अगर (!prop->name)
		जाओ out_err;

	prop->value = kmemdup(value, length, GFP_KERNEL);
	अगर (!prop->value)
		जाओ out_err;

	of_property_set_flag(prop, OF_DYNAMIC);

	prop->length = length;

	ret = of_changeset_add_property(ocs, np, prop);
	अगर (!ret)
		वापस 0;

out_err:
	kमुक्त(prop->value);
	kमुक्त(prop->name);
	kमुक्त(prop);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * LVDS Overlays
 */

RCAR_DU_OF_DTB(lvds, r8a7790);
RCAR_DU_OF_DTB(lvds, r8a7791);
RCAR_DU_OF_DTB(lvds, r8a7793);
RCAR_DU_OF_DTB(lvds, r8a7795);
RCAR_DU_OF_DTB(lvds, r8a7796);

अटल स्थिर काष्ठा rcar_du_of_overlay rcar_du_lvds_overlays[] __initस्थिर = अणु
	RCAR_DU_OF_OVERLAY(lvds, r8a7790),
	RCAR_DU_OF_OVERLAY(lvds, r8a7791),
	RCAR_DU_OF_OVERLAY(lvds, r8a7793),
	RCAR_DU_OF_OVERLAY(lvds, r8a7795),
	RCAR_DU_OF_OVERLAY(lvds, r8a7796),
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा of_changeset rcar_du_lvds_changeset;

अटल व्योम __init rcar_du_of_lvds_patch_one(काष्ठा device_node *lvds,
					     स्थिर काष्ठा of_phandle_args *clk,
					     काष्ठा device_node *local,
					     काष्ठा device_node *remote)
अणु
	अचिन्हित पूर्णांक psize;
	अचिन्हित पूर्णांक i;
	__be32 value[4];
	पूर्णांक ret;

	/*
	 * Set the LVDS घड़ीs property. This can't be perक्रमmed by the overlay
	 * as the काष्ठाure of the घड़ी specअगरier has changed over समय, and we
	 * करोn't know at compile समय which binding version the प्रणाली we will
	 * run on uses.
	 */
	अगर (clk->args_count >= ARRAY_SIZE(value) - 1)
		वापस;

	of_changeset_init(&rcar_du_lvds_changeset);

	value[0] = cpu_to_be32(clk->np->phandle);
	क्रम (i = 0; i < clk->args_count; ++i)
		value[i + 1] = cpu_to_be32(clk->args[i]);

	psize = (clk->args_count + 1) * 4;
	ret = rcar_du_of_add_property(&rcar_du_lvds_changeset, lvds,
				      "clocks", value, psize);
	अगर (ret < 0)
		जाओ करोne;

	/*
	 * Insert the node in the OF graph: patch the LVDS ports remote-endpoपूर्णांक
	 * properties to poपूर्णांक to the endpoपूर्णांकs of the sibling nodes in the
	 * graph. This can't be perक्रमmed by the overlay: on the input side the
	 * overlay would contain a phandle क्रम the DU LVDS output port that
	 * would clash with the प्रणाली DT, and on the output side the connection
	 * is board-specअगरic.
	 */
	value[0] = cpu_to_be32(local->phandle);
	value[1] = cpu_to_be32(remote->phandle);

	क्रम (i = 0; i < 2; ++i) अणु
		काष्ठा device_node *endpoपूर्णांक;

		endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(lvds, i, 0);
		अगर (!endpoपूर्णांक) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		ret = rcar_du_of_add_property(&rcar_du_lvds_changeset,
					      endpoपूर्णांक, "remote-endpoint",
					      &value[i], माप(value[i]));
		of_node_put(endpoपूर्णांक);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	ret = of_changeset_apply(&rcar_du_lvds_changeset);

करोne:
	अगर (ret < 0)
		of_changeset_destroy(&rcar_du_lvds_changeset);
पूर्ण

काष्ठा lvds_of_data अणु
	काष्ठा resource res;
	काष्ठा of_phandle_args clkspec;
	काष्ठा device_node *local;
	काष्ठा device_node *remote;
पूर्ण;

अटल व्योम __init rcar_du_of_lvds_patch(स्थिर काष्ठा of_device_id *of_ids)
अणु
	स्थिर काष्ठा rcar_du_device_info *info;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा lvds_of_data lvds_data[2] = अणु पूर्ण;
	काष्ठा device_node *lvds_node;
	काष्ठा device_node *soc_node;
	काष्ठा device_node *du_node;
	अक्षर compatible[22];
	स्थिर अक्षर *soc_name;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Get the DU node and निकास अगर not present or disabled. */
	du_node = of_find_matching_node_and_match(शून्य, of_ids, &match);
	अगर (!du_node || !of_device_is_available(du_node)) अणु
		of_node_put(du_node);
		वापस;
	पूर्ण

	info = match->data;
	soc_node = of_get_parent(du_node);

	अगर (WARN_ON(info->num_lvds > ARRAY_SIZE(lvds_data)))
		जाओ करोne;

	/*
	 * Skip अगर the LVDS nodes alपढ़ोy exists.
	 *
	 * The nodes are searched based on the compatible string, which we
	 * स्थिरruct from the SoC name found in the DU compatible string. As a
	 * match has been found we know the compatible string matches the
	 * expected क्रमmat and can thus skip some of the string manipulation
	 * normal safety checks.
	 */
	soc_name = म_अक्षर(match->compatible, '-') + 1;
	प्र_लिखो(compatible, "renesas,%s-lvds", soc_name);
	lvds_node = of_find_compatible_node(शून्य, शून्य, compatible);
	अगर (lvds_node) अणु
		of_node_put(lvds_node);
		वापस;
	पूर्ण

	/*
	 * Parse the DU node and store the रेजिस्टर specअगरier, the घड़ी
	 * specअगरier and the local and remote endpoपूर्णांक of the LVDS link क्रम
	 * later use.
	 */
	क्रम (i = 0; i < info->num_lvds; ++i) अणु
		काष्ठा lvds_of_data *lvds = &lvds_data[i];
		अचिन्हित पूर्णांक port;
		अक्षर name[7];
		पूर्णांक index;

		प्र_लिखो(name, "lvds.%u", i);
		index = of_property_match_string(du_node, "clock-names", name);
		अगर (index < 0)
			जारी;

		ret = of_parse_phandle_with_args(du_node, "clocks",
						 "#clock-cells", index,
						 &lvds->clkspec);
		अगर (ret < 0)
			जारी;

		port = info->routes[RCAR_DU_OUTPUT_LVDS0 + i].port;

		lvds->local = of_graph_get_endpoपूर्णांक_by_regs(du_node, port, 0);
		अगर (!lvds->local)
			जारी;

		lvds->remote = of_graph_get_remote_endpoपूर्णांक(lvds->local);
		अगर (!lvds->remote)
			जारी;

		index = of_property_match_string(du_node, "reg-names", name);
		अगर (index < 0)
			जारी;

		of_address_to_resource(du_node, index, &lvds->res);
	पूर्ण

	/* Parse and apply the overlay. This will resolve phandles. */
	ret = rcar_du_of_apply_overlay(rcar_du_lvds_overlays,
				       match->compatible);
	अगर (ret < 0)
		जाओ करोne;

	/* Patch the newly created LVDS encoder nodes. */
	क्रम_each_child_of_node(soc_node, lvds_node) अणु
		काष्ठा resource res;

		अगर (!of_device_is_compatible(lvds_node, compatible))
			जारी;

		/* Locate the lvds_data entry based on the resource start. */
		ret = of_address_to_resource(lvds_node, 0, &res);
		अगर (ret < 0)
			जारी;

		क्रम (i = 0; i < ARRAY_SIZE(lvds_data); ++i) अणु
			अगर (lvds_data[i].res.start == res.start)
				अवरोध;
		पूर्ण

		अगर (i == ARRAY_SIZE(lvds_data))
			जारी;

		/* Patch the LVDS encoder. */
		rcar_du_of_lvds_patch_one(lvds_node, &lvds_data[i].clkspec,
					  lvds_data[i].local,
					  lvds_data[i].remote);
	पूर्ण

करोne:
	क्रम (i = 0; i < info->num_lvds; ++i) अणु
		of_node_put(lvds_data[i].clkspec.np);
		of_node_put(lvds_data[i].local);
		of_node_put(lvds_data[i].remote);
	पूर्ण

	of_node_put(soc_node);
	of_node_put(du_node);
पूर्ण

व्योम __init rcar_du_of_init(स्थिर काष्ठा of_device_id *of_ids)
अणु
	rcar_du_of_lvds_patch(of_ids);
पूर्ण
