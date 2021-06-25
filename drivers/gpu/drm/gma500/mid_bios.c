<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

/* TODO
 * - Split functions by vbt type
 * - Make them all take drm_device
 * - Check ioremap failures
 */

#समावेश <drm/drm.h>

#समावेश "mid_bios.h"
#समावेश "psb_drv.h"

अटल व्योम mid_get_fuse_settings(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा pci_dev *pci_root =
		pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
					    0, 0);
	uपूर्णांक32_t fuse_value = 0;
	uपूर्णांक32_t fuse_value_पंचांगp = 0;

#घोषणा FB_REG06 0xD0810600
#घोषणा FB_MIPI_DISABLE  (1 << 11)
#घोषणा FB_REG09 0xD0810900
#घोषणा FB_SKU_MASK  0x7000
#घोषणा FB_SKU_SHIFT 12
#घोषणा FB_SKU_100 0
#घोषणा FB_SKU_100L 1
#घोषणा FB_SKU_83 2
	अगर (pci_root == शून्य) अणु
		WARN_ON(1);
		वापस;
	पूर्ण


	pci_ग_लिखो_config_dword(pci_root, 0xD0, FB_REG06);
	pci_पढ़ो_config_dword(pci_root, 0xD4, &fuse_value);

	/* FB_MIPI_DISABLE करोesn't mean LVDS on with Medfield */
	अगर (IS_MRST(dev))
		dev_priv->iLVDS_enable = fuse_value & FB_MIPI_DISABLE;

	DRM_INFO("internal display is %s\n",
		 dev_priv->iLVDS_enable ? "LVDS display" : "MIPI display");

	 /* Prevent runसमय suspend at start*/
	 अगर (dev_priv->iLVDS_enable) अणु
		dev_priv->is_lvds_on = true;
		dev_priv->is_mipi_on = false;
	पूर्ण अन्यथा अणु
		dev_priv->is_mipi_on = true;
		dev_priv->is_lvds_on = false;
	पूर्ण

	dev_priv->video_device_fuse = fuse_value;

	pci_ग_लिखो_config_dword(pci_root, 0xD0, FB_REG09);
	pci_पढ़ो_config_dword(pci_root, 0xD4, &fuse_value);

	dev_dbg(dev->dev, "SKU values is 0x%x.\n", fuse_value);
	fuse_value_पंचांगp = (fuse_value & FB_SKU_MASK) >> FB_SKU_SHIFT;

	dev_priv->fuse_reg_value = fuse_value;

	चयन (fuse_value_पंचांगp) अणु
	हाल FB_SKU_100:
		dev_priv->core_freq = 200;
		अवरोध;
	हाल FB_SKU_100L:
		dev_priv->core_freq = 100;
		अवरोध;
	हाल FB_SKU_83:
		dev_priv->core_freq = 166;
		अवरोध;
	शेष:
		dev_warn(dev->dev, "Invalid SKU values, SKU value = 0x%08x\n",
								fuse_value_पंचांगp);
		dev_priv->core_freq = 0;
	पूर्ण
	dev_dbg(dev->dev, "LNC core clk is %dMHz.\n", dev_priv->core_freq);
	pci_dev_put(pci_root);
पूर्ण

/*
 *	Get the revison ID, B0:D2:F0;0x08
 */
अटल व्योम mid_get_pci_revID(काष्ठा drm_psb_निजी *dev_priv)
अणु
	uपूर्णांक32_t platक्रमm_rev_id = 0;
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->dev->dev);
	पूर्णांक करोमुख्य = pci_करोमुख्य_nr(pdev->bus);
	काष्ठा pci_dev *pci_gfx_root =
		pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, PCI_DEVFN(2, 0));

	अगर (pci_gfx_root == शून्य) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	pci_पढ़ो_config_dword(pci_gfx_root, 0x08, &platक्रमm_rev_id);
	dev_priv->platक्रमm_rev_id = (uपूर्णांक8_t) platक्रमm_rev_id;
	pci_dev_put(pci_gfx_root);
	dev_dbg(dev_priv->dev->dev, "platform_rev_id is %x\n",
					dev_priv->platक्रमm_rev_id);
पूर्ण

काष्ठा mid_vbt_header अणु
	u32 signature;
	u8 revision;
पूर्ण __packed;

/* The same क्रम r0 and r1 */
काष्ठा vbt_r0 अणु
	काष्ठा mid_vbt_header vbt_header;
	u8 size;
	u8 checksum;
पूर्ण __packed;

काष्ठा vbt_r10 अणु
	काष्ठा mid_vbt_header vbt_header;
	u8 checksum;
	u16 size;
	u8 panel_count;
	u8 primary_panel_idx;
	u8 secondary_panel_idx;
	u8 __reserved[5];
पूर्ण __packed;

अटल पूर्णांक पढ़ो_vbt_r0(u32 addr, काष्ठा vbt_r0 *vbt)
अणु
	व्योम __iomem *vbt_भव;

	vbt_भव = ioremap(addr, माप(*vbt));
	अगर (vbt_भव == शून्य)
		वापस -1;

	स_नकल_fromio(vbt, vbt_भव, माप(*vbt));
	iounmap(vbt_भव);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_vbt_r10(u32 addr, काष्ठा vbt_r10 *vbt)
अणु
	व्योम __iomem *vbt_भव;

	vbt_भव = ioremap(addr, माप(*vbt));
	अगर (!vbt_भव)
		वापस -1;

	स_नकल_fromio(vbt, vbt_भव, माप(*vbt));
	iounmap(vbt_भव);

	वापस 0;
पूर्ण

अटल पूर्णांक mid_get_vbt_data_r0(काष्ठा drm_psb_निजी *dev_priv, u32 addr)
अणु
	काष्ठा vbt_r0 vbt;
	व्योम __iomem *gct_भव;
	काष्ठा gct_r0 gct;
	u8 bpi;

	अगर (पढ़ो_vbt_r0(addr, &vbt))
		वापस -1;

	gct_भव = ioremap(addr + माप(vbt), vbt.size - माप(vbt));
	अगर (!gct_भव)
		वापस -1;
	स_नकल_fromio(&gct, gct_भव, माप(gct));
	iounmap(gct_भव);

	bpi = gct.PD.BootPanelIndex;
	dev_priv->gct_data.bpi = bpi;
	dev_priv->gct_data.pt = gct.PD.PanelType;
	dev_priv->gct_data.DTD = gct.panel[bpi].DTD;
	dev_priv->gct_data.Panel_Port_Control =
		gct.panel[bpi].Panel_Port_Control;
	dev_priv->gct_data.Panel_MIPI_Display_Descriptor =
		gct.panel[bpi].Panel_MIPI_Display_Descriptor;

	वापस 0;
पूर्ण

अटल पूर्णांक mid_get_vbt_data_r1(काष्ठा drm_psb_निजी *dev_priv, u32 addr)
अणु
	काष्ठा vbt_r0 vbt;
	व्योम __iomem *gct_भव;
	काष्ठा gct_r1 gct;
	u8 bpi;

	अगर (पढ़ो_vbt_r0(addr, &vbt))
		वापस -1;

	gct_भव = ioremap(addr + माप(vbt), vbt.size - माप(vbt));
	अगर (!gct_भव)
		वापस -1;
	स_नकल_fromio(&gct, gct_भव, माप(gct));
	iounmap(gct_भव);

	bpi = gct.PD.BootPanelIndex;
	dev_priv->gct_data.bpi = bpi;
	dev_priv->gct_data.pt = gct.PD.PanelType;
	dev_priv->gct_data.DTD = gct.panel[bpi].DTD;
	dev_priv->gct_data.Panel_Port_Control =
		gct.panel[bpi].Panel_Port_Control;
	dev_priv->gct_data.Panel_MIPI_Display_Descriptor =
		gct.panel[bpi].Panel_MIPI_Display_Descriptor;

	वापस 0;
पूर्ण

अटल पूर्णांक mid_get_vbt_data_r10(काष्ठा drm_psb_निजी *dev_priv, u32 addr)
अणु
	काष्ठा vbt_r10 vbt;
	व्योम __iomem *gct_भव;
	काष्ठा gct_r10 *gct;
	काष्ठा oaktrail_timing_info *dp_ti = &dev_priv->gct_data.DTD;
	काष्ठा gct_r10_timing_info *ti;
	पूर्णांक ret = -1;

	अगर (पढ़ो_vbt_r10(addr, &vbt))
		वापस -1;

	gct = kदो_स्मृति_array(vbt.panel_count, माप(*gct), GFP_KERNEL);
	अगर (!gct)
		वापस -ENOMEM;

	gct_भव = ioremap(addr + माप(vbt),
			माप(*gct) * vbt.panel_count);
	अगर (!gct_भव)
		जाओ out;
	स_नकल_fromio(gct, gct_भव, माप(*gct));
	iounmap(gct_भव);

	dev_priv->gct_data.bpi = vbt.primary_panel_idx;
	dev_priv->gct_data.Panel_MIPI_Display_Descriptor =
		gct[vbt.primary_panel_idx].Panel_MIPI_Display_Descriptor;

	ti = &gct[vbt.primary_panel_idx].DTD;
	dp_ti->pixel_घड़ी = ti->pixel_घड़ी;
	dp_ti->hactive_hi = ti->hactive_hi;
	dp_ti->hactive_lo = ti->hactive_lo;
	dp_ti->hblank_hi = ti->hblank_hi;
	dp_ti->hblank_lo = ti->hblank_lo;
	dp_ti->hsync_offset_hi = ti->hsync_offset_hi;
	dp_ti->hsync_offset_lo = ti->hsync_offset_lo;
	dp_ti->hsync_pulse_width_hi = ti->hsync_pulse_width_hi;
	dp_ti->hsync_pulse_width_lo = ti->hsync_pulse_width_lo;
	dp_ti->vactive_hi = ti->vactive_hi;
	dp_ti->vactive_lo = ti->vactive_lo;
	dp_ti->vblank_hi = ti->vblank_hi;
	dp_ti->vblank_lo = ti->vblank_lo;
	dp_ti->vsync_offset_hi = ti->vsync_offset_hi;
	dp_ti->vsync_offset_lo = ti->vsync_offset_lo;
	dp_ti->vsync_pulse_width_hi = ti->vsync_pulse_width_hi;
	dp_ti->vsync_pulse_width_lo = ti->vsync_pulse_width_lo;

	ret = 0;
out:
	kमुक्त(gct);
	वापस ret;
पूर्ण

अटल व्योम mid_get_vbt_data(काष्ठा drm_psb_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = dev_priv->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u32 addr;
	u8 __iomem *vbt_भव;
	काष्ठा mid_vbt_header vbt_header;
	काष्ठा pci_dev *pci_gfx_root =
		pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
					    0, PCI_DEVFN(2, 0));
	पूर्णांक ret = -1;

	/* Get the address of the platक्रमm config vbt */
	pci_पढ़ो_config_dword(pci_gfx_root, 0xFC, &addr);
	pci_dev_put(pci_gfx_root);

	dev_dbg(dev->dev, "drm platform config address is %x\n", addr);

	अगर (!addr)
		जाओ out;

	/* get the भव address of the vbt */
	vbt_भव = ioremap(addr, माप(vbt_header));
	अगर (!vbt_भव)
		जाओ out;

	स_नकल_fromio(&vbt_header, vbt_भव, माप(vbt_header));
	iounmap(vbt_भव);

	अगर (स_भेद(&vbt_header.signature, "$GCT", 4))
		जाओ out;

	dev_dbg(dev->dev, "GCT revision is %02x\n", vbt_header.revision);

	चयन (vbt_header.revision) अणु
	हाल 0x00:
		ret = mid_get_vbt_data_r0(dev_priv, addr);
		अवरोध;
	हाल 0x01:
		ret = mid_get_vbt_data_r1(dev_priv, addr);
		अवरोध;
	हाल 0x10:
		ret = mid_get_vbt_data_r10(dev_priv, addr);
		अवरोध;
	शेष:
		dev_err(dev->dev, "Unknown revision of GCT!\n");
	पूर्ण

out:
	अगर (ret)
		dev_err(dev->dev, "Unable to read GCT!");
	अन्यथा
		dev_priv->has_gct = true;
पूर्ण

पूर्णांक mid_chip_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	mid_get_fuse_settings(dev);
	mid_get_vbt_data(dev_priv);
	mid_get_pci_revID(dev_priv);
	वापस 0;
पूर्ण
