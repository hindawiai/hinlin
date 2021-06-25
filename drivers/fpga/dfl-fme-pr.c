<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Management Engine (FME) Partial Reconfiguration
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Christopher Rauer <christopher.rauer@पूर्णांकel.com>
 *   Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/fpga/fpga-bridge.h>
#समावेश <linux/fpga/fpga-region.h>
#समावेश <linux/fpga-dfl.h>

#समावेश "dfl.h"
#समावेश "dfl-fme.h"
#समावेश "dfl-fme-pr.h"

अटल काष्ठा dfl_fme_region *
dfl_fme_region_find_by_port_id(काष्ठा dfl_fme *fme, पूर्णांक port_id)
अणु
	काष्ठा dfl_fme_region *fme_region;

	list_क्रम_each_entry(fme_region, &fme->region_list, node)
		अगर (fme_region->port_id == port_id)
			वापस fme_region;

	वापस शून्य;
पूर्ण

अटल पूर्णांक dfl_fme_region_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस dev->parent == data;
पूर्ण

अटल काष्ठा fpga_region *dfl_fme_region_find(काष्ठा dfl_fme *fme, पूर्णांक port_id)
अणु
	काष्ठा dfl_fme_region *fme_region;
	काष्ठा fpga_region *region;

	fme_region = dfl_fme_region_find_by_port_id(fme, port_id);
	अगर (!fme_region)
		वापस शून्य;

	region = fpga_region_class_find(शून्य, &fme_region->region->dev,
					dfl_fme_region_match);
	अगर (!region)
		वापस शून्य;

	वापस region;
पूर्ण

अटल पूर्णांक fme_pr(काष्ठा platक्रमm_device *pdev, अचिन्हित दीर्घ arg)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा dfl_fpga_fme_port_pr port_pr;
	काष्ठा fpga_image_info *info;
	काष्ठा fpga_region *region;
	व्योम __iomem *fme_hdr;
	काष्ठा dfl_fme *fme;
	अचिन्हित दीर्घ minsz;
	व्योम *buf = शून्य;
	माप_प्रकार length;
	पूर्णांक ret = 0;
	u64 v;

	minsz = दुरत्वend(काष्ठा dfl_fpga_fme_port_pr, buffer_address);

	अगर (copy_from_user(&port_pr, argp, minsz))
		वापस -EFAULT;

	अगर (port_pr.argsz < minsz || port_pr.flags)
		वापस -EINVAL;

	/* get fme header region */
	fme_hdr = dfl_get_feature_ioaddr_by_id(&pdev->dev,
					       FME_FEATURE_ID_HEADER);

	/* check port id */
	v = पढ़ोq(fme_hdr + FME_HDR_CAP);
	अगर (port_pr.port_id >= FIELD_GET(FME_CAP_NUM_PORTS, v)) अणु
		dev_dbg(&pdev->dev, "port number more than maximum\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * align PR buffer per PR bandwidth, as HW ignores the extra padding
	 * data स्वतःmatically.
	 */
	length = ALIGN(port_pr.buffer_size, 4);

	buf = vदो_स्मृति(length);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (copy_from_user(buf,
			   (व्योम __user *)(अचिन्हित दीर्घ)port_pr.buffer_address,
			   port_pr.buffer_size)) अणु
		ret = -EFAULT;
		जाओ मुक्त_निकास;
	पूर्ण

	/* prepare fpga_image_info क्रम PR */
	info = fpga_image_info_alloc(&pdev->dev);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ मुक्त_निकास;
	पूर्ण

	info->flags |= FPGA_MGR_PARTIAL_RECONFIG;

	mutex_lock(&pdata->lock);
	fme = dfl_fpga_pdata_get_निजी(pdata);
	/* fme device has been unरेजिस्टरed. */
	अगर (!fme) अणु
		ret = -EINVAL;
		जाओ unlock_निकास;
	पूर्ण

	region = dfl_fme_region_find(fme, port_pr.port_id);
	अगर (!region) अणु
		ret = -EINVAL;
		जाओ unlock_निकास;
	पूर्ण

	fpga_image_info_मुक्त(region->info);

	info->buf = buf;
	info->count = length;
	info->region_id = port_pr.port_id;
	region->info = info;

	ret = fpga_region_program_fpga(region);

	/*
	 * it allows userspace to reset the PR region's logic by disabling and
	 * reenabling the bridge to clear things out between accleration runs.
	 * so no need to hold the bridges after partial reconfiguration.
	 */
	अगर (region->get_bridges)
		fpga_bridges_put(&region->bridge_list);

	put_device(&region->dev);
unlock_निकास:
	mutex_unlock(&pdata->lock);
मुक्त_निकास:
	vमुक्त(buf);
	वापस ret;
पूर्ण

/**
 * dfl_fme_create_mgr - create fpga mgr platक्रमm device as child device
 *
 * @pdata: fme platक्रमm_device's pdata
 *
 * Return: mgr platक्रमm device अगर successful, and error code otherwise.
 */
अटल काष्ठा platक्रमm_device *
dfl_fme_create_mgr(काष्ठा dfl_feature_platक्रमm_data *pdata,
		   काष्ठा dfl_feature *feature)
अणु
	काष्ठा platक्रमm_device *mgr, *fme = pdata->dev;
	काष्ठा dfl_fme_mgr_pdata mgr_pdata;
	पूर्णांक ret = -ENOMEM;

	अगर (!feature->ioaddr)
		वापस ERR_PTR(-ENODEV);

	mgr_pdata.ioaddr = feature->ioaddr;

	/*
	 * Each FME has only one fpga-mgr, so allocate platक्रमm device using
	 * the same FME platक्रमm device id.
	 */
	mgr = platक्रमm_device_alloc(DFL_FPGA_FME_MGR, fme->id);
	अगर (!mgr)
		वापस ERR_PTR(ret);

	mgr->dev.parent = &fme->dev;

	ret = platक्रमm_device_add_data(mgr, &mgr_pdata, माप(mgr_pdata));
	अगर (ret)
		जाओ create_mgr_err;

	ret = platक्रमm_device_add(mgr);
	अगर (ret)
		जाओ create_mgr_err;

	वापस mgr;

create_mgr_err:
	platक्रमm_device_put(mgr);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * dfl_fme_destroy_mgr - destroy fpga mgr platक्रमm device
 * @pdata: fme platक्रमm device's pdata
 */
अटल व्योम dfl_fme_destroy_mgr(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_fme *priv = dfl_fpga_pdata_get_निजी(pdata);

	platक्रमm_device_unरेजिस्टर(priv->mgr);
पूर्ण

/**
 * dfl_fme_create_bridge - create fme fpga bridge platक्रमm device as child
 *
 * @pdata: fme platक्रमm device's pdata
 * @port_id: port id क्रम the bridge to be created.
 *
 * Return: bridge platक्रमm device अगर successful, and error code otherwise.
 */
अटल काष्ठा dfl_fme_bridge *
dfl_fme_create_bridge(काष्ठा dfl_feature_platक्रमm_data *pdata, पूर्णांक port_id)
अणु
	काष्ठा device *dev = &pdata->dev->dev;
	काष्ठा dfl_fme_br_pdata br_pdata;
	काष्ठा dfl_fme_bridge *fme_br;
	पूर्णांक ret = -ENOMEM;

	fme_br = devm_kzalloc(dev, माप(*fme_br), GFP_KERNEL);
	अगर (!fme_br)
		वापस ERR_PTR(ret);

	br_pdata.cdev = pdata->dfl_cdev;
	br_pdata.port_id = port_id;

	fme_br->br = platक्रमm_device_alloc(DFL_FPGA_FME_BRIDGE,
					   PLATFORM_DEVID_AUTO);
	अगर (!fme_br->br)
		वापस ERR_PTR(ret);

	fme_br->br->dev.parent = dev;

	ret = platक्रमm_device_add_data(fme_br->br, &br_pdata, माप(br_pdata));
	अगर (ret)
		जाओ create_br_err;

	ret = platक्रमm_device_add(fme_br->br);
	अगर (ret)
		जाओ create_br_err;

	वापस fme_br;

create_br_err:
	platक्रमm_device_put(fme_br->br);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * dfl_fme_destroy_bridge - destroy fpga bridge platक्रमm device
 * @fme_br: fme bridge to destroy
 */
अटल व्योम dfl_fme_destroy_bridge(काष्ठा dfl_fme_bridge *fme_br)
अणु
	platक्रमm_device_unरेजिस्टर(fme_br->br);
पूर्ण

/**
 * dfl_fme_destroy_bridge - destroy all fpga bridge platक्रमm device
 * @pdata: fme platक्रमm device's pdata
 */
अटल व्योम dfl_fme_destroy_bridges(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_fme *priv = dfl_fpga_pdata_get_निजी(pdata);
	काष्ठा dfl_fme_bridge *fbridge, *पंचांगp;

	list_क्रम_each_entry_safe(fbridge, पंचांगp, &priv->bridge_list, node) अणु
		list_del(&fbridge->node);
		dfl_fme_destroy_bridge(fbridge);
	पूर्ण
पूर्ण

/**
 * dfl_fme_create_region - create fpga region platक्रमm device as child
 *
 * @pdata: fme platक्रमm device's pdata
 * @mgr: mgr platक्रमm device needed क्रम region
 * @br: br platक्रमm device needed क्रम region
 * @port_id: port id
 *
 * Return: fme region अगर successful, and error code otherwise.
 */
अटल काष्ठा dfl_fme_region *
dfl_fme_create_region(काष्ठा dfl_feature_platक्रमm_data *pdata,
		      काष्ठा platक्रमm_device *mgr,
		      काष्ठा platक्रमm_device *br, पूर्णांक port_id)
अणु
	काष्ठा dfl_fme_region_pdata region_pdata;
	काष्ठा device *dev = &pdata->dev->dev;
	काष्ठा dfl_fme_region *fme_region;
	पूर्णांक ret = -ENOMEM;

	fme_region = devm_kzalloc(dev, माप(*fme_region), GFP_KERNEL);
	अगर (!fme_region)
		वापस ERR_PTR(ret);

	region_pdata.mgr = mgr;
	region_pdata.br = br;

	/*
	 * Each FPGA device may have more than one port, so allocate platक्रमm
	 * device using the same port platक्रमm device id.
	 */
	fme_region->region = platक्रमm_device_alloc(DFL_FPGA_FME_REGION, br->id);
	अगर (!fme_region->region)
		वापस ERR_PTR(ret);

	fme_region->region->dev.parent = dev;

	ret = platक्रमm_device_add_data(fme_region->region, &region_pdata,
				       माप(region_pdata));
	अगर (ret)
		जाओ create_region_err;

	ret = platक्रमm_device_add(fme_region->region);
	अगर (ret)
		जाओ create_region_err;

	fme_region->port_id = port_id;

	वापस fme_region;

create_region_err:
	platक्रमm_device_put(fme_region->region);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * dfl_fme_destroy_region - destroy fme region
 * @fme_region: fme region to destroy
 */
अटल व्योम dfl_fme_destroy_region(काष्ठा dfl_fme_region *fme_region)
अणु
	platक्रमm_device_unरेजिस्टर(fme_region->region);
पूर्ण

/**
 * dfl_fme_destroy_regions - destroy all fme regions
 * @pdata: fme platक्रमm device's pdata
 */
अटल व्योम dfl_fme_destroy_regions(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_fme *priv = dfl_fpga_pdata_get_निजी(pdata);
	काष्ठा dfl_fme_region *fme_region, *पंचांगp;

	list_क्रम_each_entry_safe(fme_region, पंचांगp, &priv->region_list, node) अणु
		list_del(&fme_region->node);
		dfl_fme_destroy_region(fme_region);
	पूर्ण
पूर्ण

अटल पूर्णांक pr_mgmt_init(काष्ठा platक्रमm_device *pdev,
			काष्ठा dfl_feature *feature)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा dfl_fme_region *fme_region;
	काष्ठा dfl_fme_bridge *fme_br;
	काष्ठा platक्रमm_device *mgr;
	काष्ठा dfl_fme *priv;
	व्योम __iomem *fme_hdr;
	पूर्णांक ret = -ENODEV, i = 0;
	u64 fme_cap, port_offset;

	fme_hdr = dfl_get_feature_ioaddr_by_id(&pdev->dev,
					       FME_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	priv = dfl_fpga_pdata_get_निजी(pdata);

	/* Initialize the region and bridge sub device list */
	INIT_LIST_HEAD(&priv->region_list);
	INIT_LIST_HEAD(&priv->bridge_list);

	/* Create fpga mgr platक्रमm device */
	mgr = dfl_fme_create_mgr(pdata, feature);
	अगर (IS_ERR(mgr)) अणु
		dev_err(&pdev->dev, "fail to create fpga mgr pdev\n");
		जाओ unlock;
	पूर्ण

	priv->mgr = mgr;

	/* Read capability रेजिस्टर to check number of regions and bridges */
	fme_cap = पढ़ोq(fme_hdr + FME_HDR_CAP);
	क्रम (; i < FIELD_GET(FME_CAP_NUM_PORTS, fme_cap); i++) अणु
		port_offset = पढ़ोq(fme_hdr + FME_HDR_PORT_OFST(i));
		अगर (!(port_offset & FME_PORT_OFST_IMP))
			जारी;

		/* Create bridge क्रम each port */
		fme_br = dfl_fme_create_bridge(pdata, i);
		अगर (IS_ERR(fme_br)) अणु
			ret = PTR_ERR(fme_br);
			जाओ destroy_region;
		पूर्ण

		list_add(&fme_br->node, &priv->bridge_list);

		/* Create region क्रम each port */
		fme_region = dfl_fme_create_region(pdata, mgr,
						   fme_br->br, i);
		अगर (IS_ERR(fme_region)) अणु
			ret = PTR_ERR(fme_region);
			जाओ destroy_region;
		पूर्ण

		list_add(&fme_region->node, &priv->region_list);
	पूर्ण
	mutex_unlock(&pdata->lock);

	वापस 0;

destroy_region:
	dfl_fme_destroy_regions(pdata);
	dfl_fme_destroy_bridges(pdata);
	dfl_fme_destroy_mgr(pdata);
unlock:
	mutex_unlock(&pdata->lock);
	वापस ret;
पूर्ण

अटल व्योम pr_mgmt_uinit(काष्ठा platक्रमm_device *pdev,
			  काष्ठा dfl_feature *feature)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	mutex_lock(&pdata->lock);

	dfl_fme_destroy_regions(pdata);
	dfl_fme_destroy_bridges(pdata);
	dfl_fme_destroy_mgr(pdata);
	mutex_unlock(&pdata->lock);
पूर्ण

अटल दीर्घ fme_pr_ioctl(काष्ठा platक्रमm_device *pdev,
			 काष्ठा dfl_feature *feature,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	चयन (cmd) अणु
	हाल DFL_FPGA_FME_PORT_PR:
		ret = fme_pr(pdev, arg);
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

स्थिर काष्ठा dfl_feature_id fme_pr_mgmt_id_table[] = अणु
	अणु.id = FME_FEATURE_ID_PR_MGMT,पूर्ण,
	अणु0पूर्ण
पूर्ण;

स्थिर काष्ठा dfl_feature_ops fme_pr_mgmt_ops = अणु
	.init = pr_mgmt_init,
	.uinit = pr_mgmt_uinit,
	.ioctl = fme_pr_ioctl,
पूर्ण;
