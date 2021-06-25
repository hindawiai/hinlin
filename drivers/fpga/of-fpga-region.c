<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Region - Device Tree support क्रम FPGA programming under Linux
 *
 *  Copyright (C) 2013-2016 Altera Corporation
 *  Copyright (C) 2017 Intel Corporation
 */
#समावेश <linux/fpga/fpga-bridge.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/fpga/fpga-region.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

अटल स्थिर काष्ठा of_device_id fpga_region_of_match[] = अणु
	अणु .compatible = "fpga-region", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fpga_region_of_match);

/**
 * of_fpga_region_find - find FPGA region
 * @np: device node of FPGA Region
 *
 * Caller will need to put_device(&region->dev) when करोne.
 *
 * Returns FPGA Region काष्ठा or शून्य
 */
अटल काष्ठा fpga_region *of_fpga_region_find(काष्ठा device_node *np)
अणु
	वापस fpga_region_class_find(शून्य, np, device_match_of_node);
पूर्ण

/**
 * of_fpga_region_get_mgr - get reference क्रम FPGA manager
 * @np: device node of FPGA region
 *
 * Get FPGA Manager from "fpga-mgr" property or from ancestor region.
 *
 * Caller should call fpga_mgr_put() when करोne with manager.
 *
 * Return: fpga manager काष्ठा or IS_ERR() condition containing error code.
 */
अटल काष्ठा fpga_manager *of_fpga_region_get_mgr(काष्ठा device_node *np)
अणु
	काष्ठा device_node  *mgr_node;
	काष्ठा fpga_manager *mgr;

	of_node_get(np);
	जबतक (np) अणु
		अगर (of_device_is_compatible(np, "fpga-region")) अणु
			mgr_node = of_parse_phandle(np, "fpga-mgr", 0);
			अगर (mgr_node) अणु
				mgr = of_fpga_mgr_get(mgr_node);
				of_node_put(mgr_node);
				of_node_put(np);
				वापस mgr;
			पूर्ण
		पूर्ण
		np = of_get_next_parent(np);
	पूर्ण
	of_node_put(np);

	वापस ERR_PTR(-EINVAL);
पूर्ण

/**
 * of_fpga_region_get_bridges - create a list of bridges
 * @region: FPGA region
 *
 * Create a list of bridges including the parent bridge and the bridges
 * specअगरied by "fpga-bridges" property.  Note that the
 * fpga_bridges_enable/disable/put functions are all fine with an empty list
 * अगर that happens.
 *
 * Caller should call fpga_bridges_put(&region->bridge_list) when
 * करोne with the bridges.
 *
 * Return 0 क्रम success (even अगर there are no bridges specअगरied)
 * or -EBUSY अगर any of the bridges are in use.
 */
अटल पूर्णांक of_fpga_region_get_bridges(काष्ठा fpga_region *region)
अणु
	काष्ठा device *dev = &region->dev;
	काष्ठा device_node *region_np = dev->of_node;
	काष्ठा fpga_image_info *info = region->info;
	काष्ठा device_node *br, *np, *parent_br = शून्य;
	पूर्णांक i, ret;

	/* If parent is a bridge, add to list */
	ret = of_fpga_bridge_get_to_list(region_np->parent, info,
					 &region->bridge_list);

	/* -EBUSY means parent is a bridge that is under use. Give up. */
	अगर (ret == -EBUSY)
		वापस ret;

	/* Zero वापस code means parent was a bridge and was added to list. */
	अगर (!ret)
		parent_br = region_np->parent;

	/* If overlay has a list of bridges, use it. */
	br = of_parse_phandle(info->overlay, "fpga-bridges", 0);
	अगर (br) अणु
		of_node_put(br);
		np = info->overlay;
	पूर्ण अन्यथा अणु
		np = region_np;
	पूर्ण

	क्रम (i = 0; ; i++) अणु
		br = of_parse_phandle(np, "fpga-bridges", i);
		अगर (!br)
			अवरोध;

		/* If parent bridge is in list, skip it. */
		अगर (br == parent_br) अणु
			of_node_put(br);
			जारी;
		पूर्ण

		/* If node is a bridge, get it and add to list */
		ret = of_fpga_bridge_get_to_list(br, info,
						 &region->bridge_list);
		of_node_put(br);

		/* If any of the bridges are in use, give up */
		अगर (ret == -EBUSY) अणु
			fpga_bridges_put(&region->bridge_list);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * child_regions_with_firmware
 * @overlay: device node of the overlay
 *
 * If the overlay adds child FPGA regions, they are not allowed to have
 * firmware-name property.
 *
 * Return 0 क्रम OK or -EINVAL अगर child FPGA region adds firmware-name.
 */
अटल पूर्णांक child_regions_with_firmware(काष्ठा device_node *overlay)
अणु
	काष्ठा device_node *child_region;
	स्थिर अक्षर *child_firmware_name;
	पूर्णांक ret = 0;

	of_node_get(overlay);

	child_region = of_find_matching_node(overlay, fpga_region_of_match);
	जबतक (child_region) अणु
		अगर (!of_property_पढ़ो_string(child_region, "firmware-name",
					     &child_firmware_name)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		child_region = of_find_matching_node(child_region,
						     fpga_region_of_match);
	पूर्ण

	of_node_put(child_region);

	अगर (ret)
		pr_err("firmware-name not allowed in child FPGA region: %pOF",
		       child_region);

	वापस ret;
पूर्ण

/**
 * of_fpga_region_parse_ov - parse and check overlay applied to region
 *
 * @region: FPGA region
 * @overlay: overlay applied to the FPGA region
 *
 * Given an overlay applied to a FPGA region, parse the FPGA image specअगरic
 * info in the overlay and करो some checking.
 *
 * Returns:
 *   शून्य अगर overlay करोesn't direct us to program the FPGA.
 *   fpga_image_info काष्ठा अगर there is an image to program.
 *   error code क्रम invalid overlay.
 */
अटल काष्ठा fpga_image_info *of_fpga_region_parse_ov(
						काष्ठा fpga_region *region,
						काष्ठा device_node *overlay)
अणु
	काष्ठा device *dev = &region->dev;
	काष्ठा fpga_image_info *info;
	स्थिर अक्षर *firmware_name;
	पूर्णांक ret;

	अगर (region->info) अणु
		dev_err(dev, "Region already has overlay applied.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * Reject overlay अगर child FPGA Regions added in the overlay have
	 * firmware-name property (would mean that an FPGA region that has
	 * not been added to the live tree yet is करोing FPGA programming).
	 */
	ret = child_regions_with_firmware(overlay);
	अगर (ret)
		वापस ERR_PTR(ret);

	info = fpga_image_info_alloc(dev);
	अगर (!info)
		वापस ERR_PTR(-ENOMEM);

	info->overlay = overlay;

	/* Read FPGA region properties from the overlay */
	अगर (of_property_पढ़ो_bool(overlay, "partial-fpga-config"))
		info->flags |= FPGA_MGR_PARTIAL_RECONFIG;

	अगर (of_property_पढ़ो_bool(overlay, "external-fpga-config"))
		info->flags |= FPGA_MGR_EXTERNAL_CONFIG;

	अगर (of_property_पढ़ो_bool(overlay, "encrypted-fpga-config"))
		info->flags |= FPGA_MGR_ENCRYPTED_BITSTREAM;

	अगर (!of_property_पढ़ो_string(overlay, "firmware-name",
				     &firmware_name)) अणु
		info->firmware_name = devm_kstrdup(dev, firmware_name,
						   GFP_KERNEL);
		अगर (!info->firmware_name)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	of_property_पढ़ो_u32(overlay, "region-unfreeze-timeout-us",
			     &info->enable_समयout_us);

	of_property_पढ़ो_u32(overlay, "region-freeze-timeout-us",
			     &info->disable_समयout_us);

	of_property_पढ़ो_u32(overlay, "config-complete-timeout-us",
			     &info->config_complete_समयout_us);

	/* If overlay is not programming the FPGA, करोn't need FPGA image info */
	अगर (!info->firmware_name) अणु
		ret = 0;
		जाओ ret_no_info;
	पूर्ण

	/*
	 * If overlay inक्रमms us FPGA was बाह्यally programmed, specअगरying
	 * firmware here would be ambiguous.
	 */
	अगर (info->flags & FPGA_MGR_EXTERNAL_CONFIG) अणु
		dev_err(dev, "error: specified firmware and external-fpga-config");
		ret = -EINVAL;
		जाओ ret_no_info;
	पूर्ण

	वापस info;
ret_no_info:
	fpga_image_info_मुक्त(info);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * of_fpga_region_notअगरy_pre_apply - pre-apply overlay notअगरication
 *
 * @region: FPGA region that the overlay was applied to
 * @nd: overlay notअगरication data
 *
 * Called when an overlay targeted to a FPGA Region is about to be applied.
 * Parses the overlay क्रम properties that influence how the FPGA will be
 * programmed and करोes some checking. If the checks pass, programs the FPGA.
 * If the checks fail, overlay is rejected and करोes not get added to the
 * live tree.
 *
 * Returns 0 क्रम success or negative error code क्रम failure.
 */
अटल पूर्णांक of_fpga_region_notअगरy_pre_apply(काष्ठा fpga_region *region,
					   काष्ठा of_overlay_notअगरy_data *nd)
अणु
	काष्ठा device *dev = &region->dev;
	काष्ठा fpga_image_info *info;
	पूर्णांक ret;

	info = of_fpga_region_parse_ov(region, nd->overlay);
	अगर (IS_ERR(info))
		वापस PTR_ERR(info);

	/* If overlay करोesn't program the FPGA, accept it anyway. */
	अगर (!info)
		वापस 0;

	अगर (region->info) अणु
		dev_err(dev, "Region already has overlay applied.\n");
		वापस -EINVAL;
	पूर्ण

	region->info = info;
	ret = fpga_region_program_fpga(region);
	अगर (ret) अणु
		/* error; reject overlay */
		fpga_image_info_मुक्त(info);
		region->info = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * of_fpga_region_notअगरy_post_हटाओ - post-हटाओ overlay notअगरication
 *
 * @region: FPGA region that was targeted by the overlay that was हटाओd
 * @nd: overlay notअगरication data
 *
 * Called after an overlay has been हटाओd अगर the overlay's target was a
 * FPGA region.
 */
अटल व्योम of_fpga_region_notअगरy_post_हटाओ(काष्ठा fpga_region *region,
					      काष्ठा of_overlay_notअगरy_data *nd)
अणु
	fpga_bridges_disable(&region->bridge_list);
	fpga_bridges_put(&region->bridge_list);
	fpga_image_info_मुक्त(region->info);
	region->info = शून्य;
पूर्ण

/**
 * of_fpga_region_notअगरy - reconfig notअगरier क्रम dynamic DT changes
 * @nb:		notअगरier block
 * @action:	notअगरier action
 * @arg:	reconfig data
 *
 * This notअगरier handles programming a FPGA when a "firmware-name" property is
 * added to a fpga-region.
 *
 * Returns NOTIFY_OK or error अगर FPGA programming fails.
 */
अटल पूर्णांक of_fpga_region_notअगरy(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *arg)
अणु
	काष्ठा of_overlay_notअगरy_data *nd = arg;
	काष्ठा fpga_region *region;
	पूर्णांक ret;

	चयन (action) अणु
	हाल OF_OVERLAY_PRE_APPLY:
		pr_debug("%s OF_OVERLAY_PRE_APPLY\n", __func__);
		अवरोध;
	हाल OF_OVERLAY_POST_APPLY:
		pr_debug("%s OF_OVERLAY_POST_APPLY\n", __func__);
		वापस NOTIFY_OK;       /* not क्रम us */
	हाल OF_OVERLAY_PRE_REMOVE:
		pr_debug("%s OF_OVERLAY_PRE_REMOVE\n", __func__);
		वापस NOTIFY_OK;       /* not क्रम us */
	हाल OF_OVERLAY_POST_REMOVE:
		pr_debug("%s OF_OVERLAY_POST_REMOVE\n", __func__);
		अवरोध;
	शेष:			/* should not happen */
		वापस NOTIFY_OK;
	पूर्ण

	region = of_fpga_region_find(nd->target);
	अगर (!region)
		वापस NOTIFY_OK;

	ret = 0;
	चयन (action) अणु
	हाल OF_OVERLAY_PRE_APPLY:
		ret = of_fpga_region_notअगरy_pre_apply(region, nd);
		अवरोध;

	हाल OF_OVERLAY_POST_REMOVE:
		of_fpga_region_notअगरy_post_हटाओ(region, nd);
		अवरोध;
	पूर्ण

	put_device(&region->dev);

	अगर (ret)
		वापस notअगरier_from_त्रुटि_सं(ret);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block fpga_region_of_nb = अणु
	.notअगरier_call = of_fpga_region_notअगरy,
पूर्ण;

अटल पूर्णांक of_fpga_region_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा fpga_region *region;
	काष्ठा fpga_manager *mgr;
	पूर्णांक ret;

	/* Find the FPGA mgr specअगरied by region or parent region. */
	mgr = of_fpga_region_get_mgr(np);
	अगर (IS_ERR(mgr))
		वापस -EPROBE_DEFER;

	region = devm_fpga_region_create(dev, mgr, of_fpga_region_get_bridges);
	अगर (!region) अणु
		ret = -ENOMEM;
		जाओ eprobe_mgr_put;
	पूर्ण

	ret = fpga_region_रेजिस्टर(region);
	अगर (ret)
		जाओ eprobe_mgr_put;

	of_platक्रमm_populate(np, fpga_region_of_match, शून्य, &region->dev);
	platक्रमm_set_drvdata(pdev, region);

	dev_info(dev, "FPGA Region probed\n");

	वापस 0;

eprobe_mgr_put:
	fpga_mgr_put(mgr);
	वापस ret;
पूर्ण

अटल पूर्णांक of_fpga_region_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_region *region = platक्रमm_get_drvdata(pdev);
	काष्ठा fpga_manager *mgr = region->mgr;

	fpga_region_unरेजिस्टर(region);
	fpga_mgr_put(mgr);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver of_fpga_region_driver = अणु
	.probe = of_fpga_region_probe,
	.हटाओ = of_fpga_region_हटाओ,
	.driver = अणु
		.name	= "of-fpga-region",
		.of_match_table = of_match_ptr(fpga_region_of_match),
	पूर्ण,
पूर्ण;

/**
 * fpga_region_init - init function क्रम fpga_region class
 * Creates the fpga_region class and रेजिस्टरs a reconfig notअगरier.
 */
अटल पूर्णांक __init of_fpga_region_init(व्योम)
अणु
	पूर्णांक ret;

	ret = of_overlay_notअगरier_रेजिस्टर(&fpga_region_of_nb);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&of_fpga_region_driver);
	अगर (ret)
		जाओ err_plat;

	वापस 0;

err_plat:
	of_overlay_notअगरier_unरेजिस्टर(&fpga_region_of_nb);
	वापस ret;
पूर्ण

अटल व्योम __निकास of_fpga_region_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&of_fpga_region_driver);
	of_overlay_notअगरier_unरेजिस्टर(&fpga_region_of_nb);
पूर्ण

subsys_initcall(of_fpga_region_init);
module_निकास(of_fpga_region_निकास);

MODULE_DESCRIPTION("FPGA Region");
MODULE_AUTHOR("Alan Tull <atull@kernel.org>");
MODULE_LICENSE("GPL v2");
