<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_मुख्य.c
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Alejandro Lucero <alejandro.lucero@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/devlink.h>

#समावेश "nfpcore/nfp.h"
#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfpcore/nfp_nffw.h"
#समावेश "nfpcore/nfp_nsp.h"

#समावेश "nfpcore/nfp6000_pcie.h"

#समावेश "nfp_abi.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"
#समावेश "nfp_net.h"

अटल स्थिर अक्षर nfp_driver_name[] = "nfp";

अटल स्थिर काष्ठा pci_device_id nfp_pci_device_ids[] = अणु
	अणु PCI_VENDOR_ID_NETRONOME, PCI_DEVICE_ID_NETRONOME_NFP6000,
	  PCI_VENDOR_ID_NETRONOME, PCI_ANY_ID,
	  PCI_ANY_ID, 0,
	पूर्ण,
	अणु PCI_VENDOR_ID_NETRONOME, PCI_DEVICE_ID_NETRONOME_NFP5000,
	  PCI_VENDOR_ID_NETRONOME, PCI_ANY_ID,
	  PCI_ANY_ID, 0,
	पूर्ण,
	अणु PCI_VENDOR_ID_NETRONOME, PCI_DEVICE_ID_NETRONOME_NFP4000,
	  PCI_VENDOR_ID_NETRONOME, PCI_ANY_ID,
	  PCI_ANY_ID, 0,
	पूर्ण,
	अणु 0, पूर्ण /* Required last entry. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, nfp_pci_device_ids);

पूर्णांक nfp_pf_rtsym_पढ़ो_optional(काष्ठा nfp_pf *pf, स्थिर अक्षर *क्रमmat,
			       अचिन्हित पूर्णांक शेष_val)
अणु
	अक्षर name[256];
	पूर्णांक err = 0;
	u64 val;

	snम_लिखो(name, माप(name), क्रमmat, nfp_cppcore_pcie_unit(pf->cpp));

	val = nfp_rtsym_पढ़ो_le(pf->rtbl, name, &err);
	अगर (err) अणु
		अगर (err == -ENOENT)
			वापस शेष_val;
		nfp_err(pf->cpp, "Unable to read symbol %s\n", name);
		वापस err;
	पूर्ण

	वापस val;
पूर्ण

u8 __iomem *
nfp_pf_map_rtsym(काष्ठा nfp_pf *pf, स्थिर अक्षर *name, स्थिर अक्षर *sym_fmt,
		 अचिन्हित पूर्णांक min_size, काष्ठा nfp_cpp_area **area)
अणु
	अक्षर pf_symbol[256];

	snम_लिखो(pf_symbol, माप(pf_symbol), sym_fmt,
		 nfp_cppcore_pcie_unit(pf->cpp));

	वापस nfp_rtsym_map(pf->rtbl, pf_symbol, name, min_size, area);
पूर्ण

/* Callers should hold the devlink instance lock */
पूर्णांक nfp_mbox_cmd(काष्ठा nfp_pf *pf, u32 cmd, व्योम *in_data, u64 in_length,
		 व्योम *out_data, u64 out_length)
अणु
	अचिन्हित दीर्घ err_at;
	u64 max_data_sz;
	u32 val = 0;
	पूर्णांक n, err;

	अगर (!pf->mbox)
		वापस -EOPNOTSUPP;

	max_data_sz = nfp_rtsym_size(pf->mbox) - NFP_MBOX_SYM_MIN_SIZE;

	/* Check अगर cmd field is clear */
	err = nfp_rtsym_पढ़ोl(pf->cpp, pf->mbox, NFP_MBOX_CMD, &val);
	अगर (err || val) अणु
		nfp_warn(pf->cpp, "failed to issue command (%u): %u, err: %d\n",
			 cmd, val, err);
		वापस err ?: -EBUSY;
	पूर्ण

	in_length = min(in_length, max_data_sz);
	n = nfp_rtsym_ग_लिखो(pf->cpp, pf->mbox, NFP_MBOX_DATA, in_data,
			    in_length);
	अगर (n != in_length)
		वापस -EIO;
	/* Write data_len and wipe reserved */
	err = nfp_rtsym_ग_लिखोq(pf->cpp, pf->mbox, NFP_MBOX_DATA_LEN, in_length);
	अगर (err)
		वापस err;

	/* Read back क्रम ordering */
	err = nfp_rtsym_पढ़ोl(pf->cpp, pf->mbox, NFP_MBOX_DATA_LEN, &val);
	अगर (err)
		वापस err;

	/* Write cmd and wipe वापस value */
	err = nfp_rtsym_ग_लिखोq(pf->cpp, pf->mbox, NFP_MBOX_CMD, cmd);
	अगर (err)
		वापस err;

	err_at = jअगरfies + 5 * HZ;
	जबतक (true) अणु
		/* Wait क्रम command to go to 0 (NFP_MBOX_NO_CMD) */
		err = nfp_rtsym_पढ़ोl(pf->cpp, pf->mbox, NFP_MBOX_CMD, &val);
		अगर (err)
			वापस err;
		अगर (!val)
			अवरोध;

		अगर (समय_is_beक्रमe_eq_jअगरfies(err_at))
			वापस -ETIMEDOUT;

		msleep(5);
	पूर्ण

	/* Copy output अगर any (could be error info, करो it beक्रमe पढ़ोing ret) */
	err = nfp_rtsym_पढ़ोl(pf->cpp, pf->mbox, NFP_MBOX_DATA_LEN, &val);
	अगर (err)
		वापस err;

	out_length = min_t(u32, val, min(out_length, max_data_sz));
	n = nfp_rtsym_पढ़ो(pf->cpp, pf->mbox, NFP_MBOX_DATA,
			   out_data, out_length);
	अगर (n != out_length)
		वापस -EIO;

	/* Check अगर there is an error */
	err = nfp_rtsym_पढ़ोl(pf->cpp, pf->mbox, NFP_MBOX_RET, &val);
	अगर (err)
		वापस err;
	अगर (val)
		वापस -val;

	वापस out_length;
पूर्ण

अटल bool nfp_board_पढ़ोy(काष्ठा nfp_pf *pf)
अणु
	स्थिर अक्षर *cp;
	दीर्घ state;
	पूर्णांक err;

	cp = nfp_hwinfo_lookup(pf->hwinfo, "board.state");
	अगर (!cp)
		वापस false;

	err = kम_से_दीर्घ(cp, 0, &state);
	अगर (err < 0)
		वापस false;

	वापस state == 15;
पूर्ण

अटल पूर्णांक nfp_pf_board_state_रुको(काष्ठा nfp_pf *pf)
अणु
	स्थिर अचिन्हित दीर्घ रुको_until = jअगरfies + 10 * HZ;

	जबतक (!nfp_board_पढ़ोy(pf)) अणु
		अगर (समय_is_beक्रमe_eq_jअगरfies(रुको_until)) अणु
			nfp_err(pf->cpp, "NFP board initialization timeout\n");
			वापस -EINVAL;
		पूर्ण

		nfp_info(pf->cpp, "waiting for board initialization\n");
		अगर (msleep_पूर्णांकerruptible(500))
			वापस -ERESTARTSYS;

		/* Refresh cached inक्रमmation */
		kमुक्त(pf->hwinfo);
		pf->hwinfo = nfp_hwinfo_पढ़ो(pf->cpp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_pcie_sriov_पढ़ो_nfd_limit(काष्ठा nfp_pf *pf)
अणु
	पूर्णांक err;

	pf->limit_vfs = nfp_rtsym_पढ़ो_le(pf->rtbl, "nfd_vf_cfg_max_vfs", &err);
	अगर (err) अणु
		/* For backwards compatibility अगर symbol not found allow all */
		pf->limit_vfs = ~0;
		अगर (err == -ENOENT)
			वापस 0;

		nfp_warn(pf->cpp, "Warning: VF limit read failed: %d\n", err);
		वापस err;
	पूर्ण

	err = pci_sriov_set_totalvfs(pf->pdev, pf->limit_vfs);
	अगर (err)
		nfp_warn(pf->cpp, "Failed to set VF count in sysfs: %d\n", err);
	वापस 0;
पूर्ण

अटल पूर्णांक nfp_pcie_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	काष्ठा nfp_pf *pf = pci_get_drvdata(pdev);
	पूर्णांक err;

	अगर (num_vfs > pf->limit_vfs) अणु
		nfp_info(pf->cpp, "Firmware limits number of VFs to %u\n",
			 pf->limit_vfs);
		वापस -EINVAL;
	पूर्ण

	err = pci_enable_sriov(pdev, num_vfs);
	अगर (err) अणु
		dev_warn(&pdev->dev, "Failed to enable PCI SR-IOV: %d\n", err);
		वापस err;
	पूर्ण

	mutex_lock(&pf->lock);

	err = nfp_app_sriov_enable(pf->app, num_vfs);
	अगर (err) अणु
		dev_warn(&pdev->dev,
			 "App specific PCI SR-IOV configuration failed: %d\n",
			 err);
		जाओ err_sriov_disable;
	पूर्ण

	pf->num_vfs = num_vfs;

	dev_dbg(&pdev->dev, "Created %d VFs.\n", pf->num_vfs);

	mutex_unlock(&pf->lock);
	वापस num_vfs;

err_sriov_disable:
	mutex_unlock(&pf->lock);
	pci_disable_sriov(pdev);
	वापस err;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक nfp_pcie_sriov_disable(काष्ठा pci_dev *pdev)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	काष्ठा nfp_pf *pf = pci_get_drvdata(pdev);

	mutex_lock(&pf->lock);

	/* If the VFs are asचिन्हित we cannot shut करोwn SR-IOV without
	 * causing issues, so just leave the hardware available but
	 * disabled
	 */
	अगर (pci_vfs_asचिन्हित(pdev)) अणु
		dev_warn(&pdev->dev, "Disabling while VFs assigned - VFs will not be deallocated\n");
		mutex_unlock(&pf->lock);
		वापस -EPERM;
	पूर्ण

	nfp_app_sriov_disable(pf->app);

	pf->num_vfs = 0;

	mutex_unlock(&pf->lock);

	pci_disable_sriov(pdev);
	dev_dbg(&pdev->dev, "Removed VFs.\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक nfp_pcie_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	अगर (!pci_get_drvdata(pdev))
		वापस -ENOENT;

	अगर (num_vfs == 0)
		वापस nfp_pcie_sriov_disable(pdev);
	अन्यथा
		वापस nfp_pcie_sriov_enable(pdev, num_vfs);
पूर्ण

पूर्णांक nfp_flash_update_common(काष्ठा nfp_pf *pf, स्थिर काष्ठा firmware *fw,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा device *dev = &pf->pdev->dev;
	काष्ठा nfp_nsp *nsp;
	पूर्णांक err;

	nsp = nfp_nsp_खोलो(pf->cpp);
	अगर (IS_ERR(nsp)) अणु
		err = PTR_ERR(nsp);
		अगर (extack)
			NL_SET_ERR_MSG_MOD(extack, "can't access NSP");
		अन्यथा
			dev_err(dev, "Failed to access the NSP: %d\n", err);
		वापस err;
	पूर्ण

	err = nfp_nsp_ग_लिखो_flash(nsp, fw);
	अगर (err < 0)
		जाओ निकास_बंद_nsp;
	dev_info(dev, "Finished writing flash image\n");
	err = 0;

निकास_बंद_nsp:
	nfp_nsp_बंद(nsp);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा firmware *
nfp_net_fw_request(काष्ठा pci_dev *pdev, काष्ठा nfp_pf *pf, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक err;

	err = request_firmware_direct(&fw, name, &pdev->dev);
	nfp_info(pf->cpp, "  %s: %s\n",
		 name, err ? "not found" : "found");
	अगर (err)
		वापस शून्य;

	वापस fw;
पूर्ण

/**
 * nfp_net_fw_find() - Find the correct firmware image क्रम netdev mode
 * @pdev:	PCI Device काष्ठाure
 * @pf:		NFP PF Device काष्ठाure
 *
 * Return: firmware अगर found and requested successfully.
 */
अटल स्थिर काष्ठा firmware *
nfp_net_fw_find(काष्ठा pci_dev *pdev, काष्ठा nfp_pf *pf)
अणु
	काष्ठा nfp_eth_table_port *port;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_model;
	अक्षर fw_name[256];
	स्थिर u8 *serial;
	u16 पूर्णांकerface;
	पूर्णांक spc, i, j;

	nfp_info(pf->cpp, "Looking for firmware file in order of priority:\n");

	/* First try to find a firmware image specअगरic क्रम this device */
	पूर्णांकerface = nfp_cpp_पूर्णांकerface(pf->cpp);
	nfp_cpp_serial(pf->cpp, &serial);
	प्र_लिखो(fw_name, "netronome/serial-%pMF-%02hhx-%02hhx.nffw",
		serial, पूर्णांकerface >> 8, पूर्णांकerface & 0xff);
	fw = nfp_net_fw_request(pdev, pf, fw_name);
	अगर (fw)
		वापस fw;

	/* Then try the PCI name */
	प्र_लिखो(fw_name, "netronome/pci-%s.nffw", pci_name(pdev));
	fw = nfp_net_fw_request(pdev, pf, fw_name);
	अगर (fw)
		वापस fw;

	/* Finally try the card type and media */
	अगर (!pf->eth_tbl) अणु
		dev_err(&pdev->dev, "Error: can't identify media config\n");
		वापस शून्य;
	पूर्ण

	fw_model = nfp_hwinfo_lookup(pf->hwinfo, "assembly.partno");
	अगर (!fw_model) अणु
		dev_err(&pdev->dev, "Error: can't read part number\n");
		वापस शून्य;
	पूर्ण

	spc = ARRAY_SIZE(fw_name);
	spc -= snम_लिखो(fw_name, spc, "netronome/nic_%s", fw_model);

	क्रम (i = 0; spc > 0 && i < pf->eth_tbl->count; i += j) अणु
		port = &pf->eth_tbl->ports[i];
		j = 1;
		जबतक (i + j < pf->eth_tbl->count &&
		       port->speed == port[j].speed)
			j++;

		spc -= snम_लिखो(&fw_name[ARRAY_SIZE(fw_name) - spc], spc,
				"_%dx%d", j, port->speed / 1000);
	पूर्ण

	अगर (spc <= 0)
		वापस शून्य;

	spc -= snम_लिखो(&fw_name[ARRAY_SIZE(fw_name) - spc], spc, ".nffw");
	अगर (spc <= 0)
		वापस शून्य;

	वापस nfp_net_fw_request(pdev, pf, fw_name);
पूर्ण

अटल पूर्णांक
nfp_get_fw_policy_value(काष्ठा pci_dev *pdev, काष्ठा nfp_nsp *nsp,
			स्थिर अक्षर *key, स्थिर अक्षर *शेष_val, पूर्णांक max_val,
			पूर्णांक *value)
अणु
	अक्षर hwinfo[64];
	दीर्घ hi_val;
	पूर्णांक err;

	snम_लिखो(hwinfo, माप(hwinfo), key);
	err = nfp_nsp_hwinfo_lookup_optional(nsp, hwinfo, माप(hwinfo),
					     शेष_val);
	अगर (err)
		वापस err;

	err = kम_से_दीर्घ(hwinfo, 0, &hi_val);
	अगर (err || hi_val < 0 || hi_val > max_val) अणु
		dev_warn(&pdev->dev,
			 "Invalid value '%s' from '%s', ignoring\n",
			 hwinfo, key);
		err = kम_से_दीर्घ(शेष_val, 0, &hi_val);
	पूर्ण

	*value = hi_val;
	वापस err;
पूर्ण

/**
 * nfp_fw_load() - Load the firmware image
 * @pdev:       PCI Device काष्ठाure
 * @pf:		NFP PF Device काष्ठाure
 * @nsp:	NFP SP handle
 *
 * Return: -ERRNO, 0 क्रम no firmware loaded, 1 क्रम firmware loaded
 */
अटल पूर्णांक
nfp_fw_load(काष्ठा pci_dev *pdev, काष्ठा nfp_pf *pf, काष्ठा nfp_nsp *nsp)
अणु
	bool करो_reset, fw_loaded = false;
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक err, reset, policy, अगरcs = 0;
	अक्षर *token, *ptr;
	अक्षर hwinfo[64];
	u16 पूर्णांकerface;

	snम_लिखो(hwinfo, माप(hwinfo), "abi_drv_load_ifc");
	err = nfp_nsp_hwinfo_lookup_optional(nsp, hwinfo, माप(hwinfo),
					     NFP_NSP_DRV_LOAD_IFC_DEFAULT);
	अगर (err)
		वापस err;

	पूर्णांकerface = nfp_cpp_पूर्णांकerface(pf->cpp);
	ptr = hwinfo;
	जबतक ((token = strsep(&ptr, ","))) अणु
		अचिन्हित दीर्घ पूर्णांकerface_hi;

		err = kम_से_अदीर्घ(token, 0, &पूर्णांकerface_hi);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Failed to parse interface '%s': %d\n",
				token, err);
			वापस err;
		पूर्ण

		अगरcs++;
		अगर (पूर्णांकerface == पूर्णांकerface_hi)
			अवरोध;
	पूर्ण

	अगर (!token) अणु
		dev_info(&pdev->dev, "Firmware will be loaded by partner\n");
		वापस 0;
	पूर्ण

	err = nfp_get_fw_policy_value(pdev, nsp, "abi_drv_reset",
				      NFP_NSP_DRV_RESET_DEFAULT,
				      NFP_NSP_DRV_RESET_NEVER, &reset);
	अगर (err)
		वापस err;

	err = nfp_get_fw_policy_value(pdev, nsp, "app_fw_from_flash",
				      NFP_NSP_APP_FW_LOAD_DEFAULT,
				      NFP_NSP_APP_FW_LOAD_PREF, &policy);
	अगर (err)
		वापस err;

	fw = nfp_net_fw_find(pdev, pf);
	करो_reset = reset == NFP_NSP_DRV_RESET_ALWAYS ||
		   (fw && reset == NFP_NSP_DRV_RESET_DISK);

	अगर (करो_reset) अणु
		dev_info(&pdev->dev, "Soft-resetting the NFP\n");
		err = nfp_nsp_device_soft_reset(nsp);
		अगर (err < 0) अणु
			dev_err(&pdev->dev,
				"Failed to soft reset the NFP: %d\n", err);
			जाओ निकास_release_fw;
		पूर्ण
	पूर्ण

	अगर (fw && policy != NFP_NSP_APP_FW_LOAD_FLASH) अणु
		अगर (nfp_nsp_has_fw_loaded(nsp) && nfp_nsp_fw_loaded(nsp))
			जाओ निकास_release_fw;

		err = nfp_nsp_load_fw(nsp, fw);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "FW loading failed: %d\n",
				err);
			जाओ निकास_release_fw;
		पूर्ण
		dev_info(&pdev->dev, "Finished loading FW image\n");
		fw_loaded = true;
	पूर्ण अन्यथा अगर (policy != NFP_NSP_APP_FW_LOAD_DISK &&
		   nfp_nsp_has_stored_fw_load(nsp)) अणु

		/* Don't propagate this error to stick with legacy driver
		 * behavior, failure will be detected later during init.
		 */
		अगर (!nfp_nsp_load_stored_fw(nsp))
			dev_info(&pdev->dev, "Finished loading stored FW image\n");

		/* Don't flag the fw_loaded in this हाल since other devices
		 * may reuse the firmware when configured this way
		 */
	पूर्ण अन्यथा अणु
		dev_warn(&pdev->dev, "Didn't load firmware, please update flash or reconfigure card\n");
	पूर्ण

निकास_release_fw:
	release_firmware(fw);

	/* We करोn't want to unload firmware when other devices may still be
	 * dependent on it, which could be the हाल अगर there are multiple
	 * devices that could load firmware.
	 */
	अगर (fw_loaded && अगरcs == 1)
		pf->unload_fw_on_हटाओ = true;

	वापस err < 0 ? err : fw_loaded;
पूर्ण

अटल व्योम
nfp_nsp_init_ports(काष्ठा pci_dev *pdev, काष्ठा nfp_pf *pf,
		   काष्ठा nfp_nsp *nsp)
अणु
	bool needs_reinit = false;
	पूर्णांक i;

	pf->eth_tbl = __nfp_eth_पढ़ो_ports(pf->cpp, nsp);
	अगर (!pf->eth_tbl)
		वापस;

	अगर (!nfp_nsp_has_mac_reinit(nsp))
		वापस;

	क्रम (i = 0; i < pf->eth_tbl->count; i++)
		needs_reinit |= pf->eth_tbl->ports[i].override_changed;
	अगर (!needs_reinit)
		वापस;

	kमुक्त(pf->eth_tbl);
	अगर (nfp_nsp_mac_reinit(nsp))
		dev_warn(&pdev->dev, "MAC reinit failed\n");

	pf->eth_tbl = __nfp_eth_पढ़ो_ports(pf->cpp, nsp);
पूर्ण

अटल पूर्णांक nfp_nsp_init(काष्ठा pci_dev *pdev, काष्ठा nfp_pf *pf)
अणु
	काष्ठा nfp_nsp *nsp;
	पूर्णांक err;

	err = nfp_resource_रुको(pf->cpp, NFP_RESOURCE_NSP, 30);
	अगर (err)
		वापस err;

	nsp = nfp_nsp_खोलो(pf->cpp);
	अगर (IS_ERR(nsp)) अणु
		err = PTR_ERR(nsp);
		dev_err(&pdev->dev, "Failed to access the NSP: %d\n", err);
		वापस err;
	पूर्ण

	err = nfp_nsp_रुको(nsp);
	अगर (err < 0)
		जाओ निकास_बंद_nsp;

	nfp_nsp_init_ports(pdev, pf, nsp);

	pf->nspi = __nfp_nsp_identअगरy(nsp);
	अगर (pf->nspi)
		dev_info(&pdev->dev, "BSP: %s\n", pf->nspi->version);

	err = nfp_fw_load(pdev, pf, nsp);
	अगर (err < 0) अणु
		kमुक्त(pf->nspi);
		kमुक्त(pf->eth_tbl);
		dev_err(&pdev->dev, "Failed to load FW\n");
		जाओ निकास_बंद_nsp;
	पूर्ण

	pf->fw_loaded = !!err;
	err = 0;

निकास_बंद_nsp:
	nfp_nsp_बंद(nsp);

	वापस err;
पूर्ण

अटल व्योम nfp_fw_unload(काष्ठा nfp_pf *pf)
अणु
	काष्ठा nfp_nsp *nsp;
	पूर्णांक err;

	nsp = nfp_nsp_खोलो(pf->cpp);
	अगर (IS_ERR(nsp)) अणु
		nfp_err(pf->cpp, "Reset failed, can't open NSP\n");
		वापस;
	पूर्ण

	err = nfp_nsp_device_soft_reset(nsp);
	अगर (err < 0)
		dev_warn(&pf->pdev->dev, "Couldn't unload firmware: %d\n", err);
	अन्यथा
		dev_info(&pf->pdev->dev, "Firmware safely unloaded\n");

	nfp_nsp_बंद(nsp);
पूर्ण

अटल पूर्णांक nfp_pf_find_rtsyms(काष्ठा nfp_pf *pf)
अणु
	अक्षर pf_symbol[256];
	अचिन्हित पूर्णांक pf_id;

	pf_id = nfp_cppcore_pcie_unit(pf->cpp);

	/* Optional per-PCI PF mailbox */
	snम_लिखो(pf_symbol, माप(pf_symbol), NFP_MBOX_SYM_NAME, pf_id);
	pf->mbox = nfp_rtsym_lookup(pf->rtbl, pf_symbol);
	अगर (pf->mbox && nfp_rtsym_size(pf->mbox) < NFP_MBOX_SYM_MIN_SIZE) अणु
		nfp_err(pf->cpp, "PF mailbox symbol too small: %llu < %d\n",
			nfp_rtsym_size(pf->mbox), NFP_MBOX_SYM_MIN_SIZE);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_pci_probe(काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा devlink *devlink;
	काष्ठा nfp_pf *pf;
	पूर्णांक err;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_NETRONOME &&
	    pdev->device == PCI_DEVICE_ID_NETRONOME_NFP6000_VF)
		dev_warn(&pdev->dev, "Binding NFP VF device to the NFP PF driver, the VF driver is called 'nfp_netvf'\n");

	err = pci_enable_device(pdev);
	अगर (err < 0)
		वापस err;

	pci_set_master(pdev);

	err = dma_set_mask_and_coherent(&pdev->dev,
					DMA_BIT_MASK(NFP_NET_MAX_DMA_BITS));
	अगर (err)
		जाओ err_pci_disable;

	err = pci_request_regions(pdev, nfp_driver_name);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Unable to reserve pci resources.\n");
		जाओ err_pci_disable;
	पूर्ण

	devlink = devlink_alloc(&nfp_devlink_ops, माप(*pf));
	अगर (!devlink) अणु
		err = -ENOMEM;
		जाओ err_rel_regions;
	पूर्ण
	pf = devlink_priv(devlink);
	INIT_LIST_HEAD(&pf->vnics);
	INIT_LIST_HEAD(&pf->ports);
	mutex_init(&pf->lock);
	pci_set_drvdata(pdev, pf);
	pf->pdev = pdev;

	pf->wq = alloc_workqueue("nfp-%s", 0, 2, pci_name(pdev));
	अगर (!pf->wq) अणु
		err = -ENOMEM;
		जाओ err_pci_priv_unset;
	पूर्ण

	pf->cpp = nfp_cpp_from_nfp6000_pcie(pdev);
	अगर (IS_ERR(pf->cpp)) अणु
		err = PTR_ERR(pf->cpp);
		जाओ err_disable_msix;
	पूर्ण

	err = nfp_resource_table_init(pf->cpp);
	अगर (err)
		जाओ err_cpp_मुक्त;

	pf->hwinfo = nfp_hwinfo_पढ़ो(pf->cpp);

	dev_info(&pdev->dev, "Assembly: %s%s%s-%s CPLD: %s\n",
		 nfp_hwinfo_lookup(pf->hwinfo, "assembly.vendor"),
		 nfp_hwinfo_lookup(pf->hwinfo, "assembly.partno"),
		 nfp_hwinfo_lookup(pf->hwinfo, "assembly.serial"),
		 nfp_hwinfo_lookup(pf->hwinfo, "assembly.revision"),
		 nfp_hwinfo_lookup(pf->hwinfo, "cpld.version"));

	err = nfp_pf_board_state_रुको(pf);
	अगर (err)
		जाओ err_hwinfo_मुक्त;

	err = nfp_nsp_init(pdev, pf);
	अगर (err)
		जाओ err_hwinfo_मुक्त;

	pf->mip = nfp_mip_खोलो(pf->cpp);
	pf->rtbl = __nfp_rtsym_table_पढ़ो(pf->cpp, pf->mip);

	err = nfp_pf_find_rtsyms(pf);
	अगर (err)
		जाओ err_fw_unload;

	pf->dump_flag = NFP_DUMP_NSP_DIAG;
	pf->dumpspec = nfp_net_dump_load_dumpspec(pf->cpp, pf->rtbl);

	err = nfp_pcie_sriov_पढ़ो_nfd_limit(pf);
	अगर (err)
		जाओ err_fw_unload;

	pf->num_vfs = pci_num_vf(pdev);
	अगर (pf->num_vfs > pf->limit_vfs) अणु
		dev_err(&pdev->dev,
			"Error: %d VFs already enabled, but loaded FW can only support %d\n",
			pf->num_vfs, pf->limit_vfs);
		err = -EINVAL;
		जाओ err_fw_unload;
	पूर्ण

	err = nfp_net_pci_probe(pf);
	अगर (err)
		जाओ err_fw_unload;

	err = nfp_hwmon_रेजिस्टर(pf);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register hwmon info\n");
		जाओ err_net_हटाओ;
	पूर्ण

	वापस 0;

err_net_हटाओ:
	nfp_net_pci_हटाओ(pf);
err_fw_unload:
	kमुक्त(pf->rtbl);
	nfp_mip_बंद(pf->mip);
	अगर (pf->unload_fw_on_हटाओ)
		nfp_fw_unload(pf);
	kमुक्त(pf->eth_tbl);
	kमुक्त(pf->nspi);
	vमुक्त(pf->dumpspec);
err_hwinfo_मुक्त:
	kमुक्त(pf->hwinfo);
err_cpp_मुक्त:
	nfp_cpp_मुक्त(pf->cpp);
err_disable_msix:
	destroy_workqueue(pf->wq);
err_pci_priv_unset:
	pci_set_drvdata(pdev, शून्य);
	mutex_destroy(&pf->lock);
	devlink_मुक्त(devlink);
err_rel_regions:
	pci_release_regions(pdev);
err_pci_disable:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम __nfp_pci_shutकरोwn(काष्ठा pci_dev *pdev, bool unload_fw)
अणु
	काष्ठा nfp_pf *pf;

	pf = pci_get_drvdata(pdev);
	अगर (!pf)
		वापस;

	nfp_hwmon_unरेजिस्टर(pf);

	nfp_pcie_sriov_disable(pdev);

	nfp_net_pci_हटाओ(pf);

	vमुक्त(pf->dumpspec);
	kमुक्त(pf->rtbl);
	nfp_mip_बंद(pf->mip);
	अगर (unload_fw && pf->unload_fw_on_हटाओ)
		nfp_fw_unload(pf);

	destroy_workqueue(pf->wq);
	pci_set_drvdata(pdev, शून्य);
	kमुक्त(pf->hwinfo);
	nfp_cpp_मुक्त(pf->cpp);

	kमुक्त(pf->eth_tbl);
	kमुक्त(pf->nspi);
	mutex_destroy(&pf->lock);
	devlink_मुक्त(priv_to_devlink(pf));
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल व्योम nfp_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	__nfp_pci_shutकरोwn(pdev, true);
पूर्ण

अटल व्योम nfp_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	__nfp_pci_shutकरोwn(pdev, false);
पूर्ण

अटल काष्ठा pci_driver nfp_pci_driver = अणु
	.name			= nfp_driver_name,
	.id_table		= nfp_pci_device_ids,
	.probe			= nfp_pci_probe,
	.हटाओ			= nfp_pci_हटाओ,
	.shutकरोwn		= nfp_pci_shutकरोwn,
	.sriov_configure	= nfp_pcie_sriov_configure,
पूर्ण;

अटल पूर्णांक __init nfp_मुख्य_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("%s: NFP PCIe Driver, Copyright (C) 2014-2017 Netronome Systems\n",
		nfp_driver_name);

	nfp_net_debugfs_create();

	err = pci_रेजिस्टर_driver(&nfp_pci_driver);
	अगर (err < 0)
		जाओ err_destroy_debugfs;

	err = pci_रेजिस्टर_driver(&nfp_netvf_pci_driver);
	अगर (err)
		जाओ err_unreg_pf;

	वापस err;

err_unreg_pf:
	pci_unरेजिस्टर_driver(&nfp_pci_driver);
err_destroy_debugfs:
	nfp_net_debugfs_destroy();
	वापस err;
पूर्ण

अटल व्योम __निकास nfp_मुख्य_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&nfp_netvf_pci_driver);
	pci_unरेजिस्टर_driver(&nfp_pci_driver);
	nfp_net_debugfs_destroy();
पूर्ण

module_init(nfp_मुख्य_init);
module_निकास(nfp_मुख्य_निकास);

MODULE_FIRMWARE("netronome/nic_AMDA0058-0011_2x40.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0058-0012_2x40.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0081-0001_1x40.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0081-0001_4x10.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0096-0001_2x10.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0097-0001_2x40.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0097-0001_4x10_1x40.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0097-0001_8x10.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0099-0001_2x10.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0099-0001_2x25.nffw");
MODULE_FIRMWARE("netronome/nic_AMDA0099-0001_1x10_1x25.nffw");

MODULE_AUTHOR("Netronome Systems <oss-drivers@netronome.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("The Netronome Flow Processor (NFP) driver.");
