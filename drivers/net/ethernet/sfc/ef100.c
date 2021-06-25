<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2018 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "net_driver.h"
#समावेश <linux/module.h>
#समावेश <linux/aer.h>
#समावेश "efx_common.h"
#समावेश "efx_channels.h"
#समावेश "io.h"
#समावेश "ef100_nic.h"
#समावेश "ef100_netdev.h"
#समावेश "ef100_regs.h"
#समावेश "ef100.h"

#घोषणा EFX_EF100_PCI_DEFAULT_BAR	2

/* Number of bytes at start of venकरोr specअगरied extended capability that indicate
 * that the capability is venकरोr specअगरied. i.e. offset from value वापसed by
 * pci_find_next_ext_capability() to beginning of venकरोr specअगरied capability
 * header.
 */
#घोषणा PCI_EXT_CAP_HDR_LENGTH  4

/* Expected size of a Xilinx continuation address table entry. */
#घोषणा ESE_GZ_CFGBAR_CONT_CAP_MIN_LENGTH      16

काष्ठा ef100_func_ctl_winकरोw अणु
	bool valid;
	अचिन्हित पूर्णांक bar;
	u64 offset;
पूर्ण;

अटल पूर्णांक ef100_pci_walk_xilinx_table(काष्ठा efx_nic *efx, u64 offset,
				       काष्ठा ef100_func_ctl_winकरोw *result);

/* Number of bytes to offset when पढ़ोing bit position x with dword accessors. */
#घोषणा ROUND_DOWN_TO_DWORD(x) (((x) & (~31)) >> 3)

#घोषणा EXTRACT_BITS(x, lbn, width) \
	(((x) >> ((lbn) & 31)) & ((1ull << (width)) - 1))

अटल u32 _ef100_pci_get_bar_bits_with_width(काष्ठा efx_nic *efx,
					      पूर्णांक काष्ठाure_start,
					      पूर्णांक lbn, पूर्णांक width)
अणु
	efx_dword_t dword;

	efx_पढ़ोd(efx, &dword, काष्ठाure_start + ROUND_DOWN_TO_DWORD(lbn));

	वापस EXTRACT_BITS(le32_to_cpu(dword.u32[0]), lbn, width);
पूर्ण

#घोषणा ef100_pci_get_bar_bits(efx, entry_location, bitdef)	\
	_ef100_pci_get_bar_bits_with_width(efx, entry_location,	\
		ESF_GZ_CFGBAR_ ## bitdef ## _LBN,		\
		ESF_GZ_CFGBAR_ ## bitdef ## _WIDTH)

अटल पूर्णांक ef100_pci_parse_ef100_entry(काष्ठा efx_nic *efx, पूर्णांक entry_location,
				       काष्ठा ef100_func_ctl_winकरोw *result)
अणु
	u64 offset = ef100_pci_get_bar_bits(efx, entry_location, EF100_FUNC_CTL_WIN_OFF) <<
					ESE_GZ_EF100_FUNC_CTL_WIN_OFF_SHIFT;
	u32 bar = ef100_pci_get_bar_bits(efx, entry_location, EF100_BAR);

	netअगर_dbg(efx, probe, efx->net_dev,
		  "Found EF100 function control window bar=%d offset=0x%llx\n",
		  bar, offset);

	अगर (result->valid) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Duplicated EF100 table entry.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (bar == ESE_GZ_CFGBAR_EF100_BAR_NUM_EXPANSION_ROM ||
	    bar == ESE_GZ_CFGBAR_EF100_BAR_NUM_INVALID) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Bad BAR value of %d in Xilinx capabilities EF100 entry.\n",
			  bar);
		वापस -EINVAL;
	पूर्ण

	result->bar = bar;
	result->offset = offset;
	result->valid = true;
	वापस 0;
पूर्ण

अटल bool ef100_pci_करोes_bar_overflow(काष्ठा efx_nic *efx, पूर्णांक bar,
					u64 next_entry)
अणु
	वापस next_entry + ESE_GZ_CFGBAR_ENTRY_HEADER_SIZE >
					pci_resource_len(efx->pci_dev, bar);
पूर्ण

/* Parse a Xilinx capabilities table entry describing a continuation to a new
 * sub-table.
 */
अटल पूर्णांक ef100_pci_parse_जारी_entry(काष्ठा efx_nic *efx, पूर्णांक entry_location,
					  काष्ठा ef100_func_ctl_winकरोw *result)
अणु
	अचिन्हित पूर्णांक previous_bar;
	efx_oword_t entry;
	u64 offset;
	पूर्णांक rc = 0;
	u32 bar;

	efx_पढ़ोo(efx, &entry, entry_location);

	bar = EFX_OWORD_FIELD32(entry, ESF_GZ_CFGBAR_CONT_CAP_BAR);

	offset = EFX_OWORD_FIELD64(entry, ESF_GZ_CFGBAR_CONT_CAP_OFFSET) <<
		ESE_GZ_CONT_CAP_OFFSET_BYTES_SHIFT;

	previous_bar = efx->mem_bar;

	अगर (bar == ESE_GZ_VSEC_BAR_NUM_EXPANSION_ROM ||
	    bar == ESE_GZ_VSEC_BAR_NUM_INVALID) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Bad BAR value of %d in Xilinx capabilities sub-table.\n",
			  bar);
		वापस -EINVAL;
	पूर्ण

	अगर (bar != previous_bar) अणु
		efx_fini_io(efx);

		अगर (ef100_pci_करोes_bar_overflow(efx, bar, offset)) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Xilinx table will overrun BAR[%d] offset=0x%llx\n",
				  bar, offset);
			वापस -EINVAL;
		पूर्ण

		/* Temporarily map new BAR. */
		rc = efx_init_io(efx, bar,
				 (dma_addr_t)DMA_BIT_MASK(ESF_GZ_TX_SEND_ADDR_WIDTH),
				 pci_resource_len(efx->pci_dev, bar));
		अगर (rc) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Mapping new BAR for Xilinx table failed, rc=%d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	rc = ef100_pci_walk_xilinx_table(efx, offset, result);
	अगर (rc)
		वापस rc;

	अगर (bar != previous_bar) अणु
		efx_fini_io(efx);

		/* Put old BAR back. */
		rc = efx_init_io(efx, previous_bar,
				 (dma_addr_t)DMA_BIT_MASK(ESF_GZ_TX_SEND_ADDR_WIDTH),
				 pci_resource_len(efx->pci_dev, previous_bar));
		अगर (rc) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Putting old BAR back failed, rc=%d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Iterate over the Xilinx capabilities table in the currently mapped BAR and
 * call ef100_pci_parse_ef100_entry() on any EF100 entries and
 * ef100_pci_parse_जारी_entry() on any table continuations.
 */
अटल पूर्णांक ef100_pci_walk_xilinx_table(काष्ठा efx_nic *efx, u64 offset,
				       काष्ठा ef100_func_ctl_winकरोw *result)
अणु
	u64 current_entry = offset;
	पूर्णांक rc = 0;

	जबतक (true) अणु
		u32 id = ef100_pci_get_bar_bits(efx, current_entry, ENTRY_FORMAT);
		u32 last = ef100_pci_get_bar_bits(efx, current_entry, ENTRY_LAST);
		u32 rev = ef100_pci_get_bar_bits(efx, current_entry, ENTRY_REV);
		u32 entry_size;

		अगर (id == ESE_GZ_CFGBAR_ENTRY_LAST)
			वापस 0;

		entry_size = ef100_pci_get_bar_bits(efx, current_entry, ENTRY_SIZE);

		netअगर_dbg(efx, probe, efx->net_dev,
			  "Seen Xilinx table entry 0x%x size 0x%x at 0x%llx in BAR[%d]\n",
			  id, entry_size, current_entry, efx->mem_bar);

		अगर (entry_size < माप(u32) * 2) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Xilinx table entry too short len=0x%x\n", entry_size);
			वापस -EINVAL;
		पूर्ण

		चयन (id) अणु
		हाल ESE_GZ_CFGBAR_ENTRY_EF100:
			अगर (rev != ESE_GZ_CFGBAR_ENTRY_REV_EF100 ||
			    entry_size < ESE_GZ_CFGBAR_ENTRY_SIZE_EF100) अणु
				netअगर_err(efx, probe, efx->net_dev,
					  "Bad length or rev for EF100 entry in Xilinx capabilities table. entry_size=%d rev=%d.\n",
					  entry_size, rev);
				वापस -EINVAL;
			पूर्ण

			rc = ef100_pci_parse_ef100_entry(efx, current_entry,
							 result);
			अगर (rc)
				वापस rc;
			अवरोध;
		हाल ESE_GZ_CFGBAR_ENTRY_CONT_CAP_ADDR:
			अगर (rev != 0 || entry_size < ESE_GZ_CFGBAR_CONT_CAP_MIN_LENGTH) अणु
				netअगर_err(efx, probe, efx->net_dev,
					  "Bad length or rev for continue entry in Xilinx capabilities table. entry_size=%d rev=%d.\n",
					  entry_size, rev);
				वापस -EINVAL;
			पूर्ण

			rc = ef100_pci_parse_जारी_entry(efx, current_entry, result);
			अगर (rc)
				वापस rc;
			अवरोध;
		शेष:
			/* Ignore unknown table entries. */
			अवरोध;
		पूर्ण

		अगर (last)
			वापस 0;

		current_entry += entry_size;

		अगर (ef100_pci_करोes_bar_overflow(efx, efx->mem_bar, current_entry)) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Xilinx table overrun at position=0x%llx.\n",
				  current_entry);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक _ef100_pci_get_config_bits_with_width(काष्ठा efx_nic *efx,
						 पूर्णांक काष्ठाure_start, पूर्णांक lbn,
						 पूर्णांक width, u32 *result)
अणु
	पूर्णांक rc, pos = काष्ठाure_start + ROUND_DOWN_TO_DWORD(lbn);
	u32 temp;

	rc = pci_पढ़ो_config_dword(efx->pci_dev, pos, &temp);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Failed to read PCI config dword at %d\n",
			  pos);
		वापस rc;
	पूर्ण

	*result = EXTRACT_BITS(temp, lbn, width);

	वापस 0;
पूर्ण

#घोषणा ef100_pci_get_config_bits(efx, entry_location, bitdef, result)	\
	_ef100_pci_get_config_bits_with_width(efx, entry_location,	\
		 ESF_GZ_VSEC_ ## bitdef ## _LBN,			\
		 ESF_GZ_VSEC_ ## bitdef ## _WIDTH, result)

/* Call ef100_pci_walk_xilinx_table() क्रम the Xilinx capabilities table poपूर्णांकed
 * to by this PCI_EXT_CAP_ID_VNDR.
 */
अटल पूर्णांक ef100_pci_parse_xilinx_cap(काष्ठा efx_nic *efx, पूर्णांक vndr_cap,
				      bool has_offset_hi,
				      काष्ठा ef100_func_ctl_winकरोw *result)
अणु
	u32 offset_high = 0;
	u32 offset_lo = 0;
	u64 offset = 0;
	u32 bar = 0;
	पूर्णांक rc = 0;

	rc = ef100_pci_get_config_bits(efx, vndr_cap, TBL_BAR, &bar);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Failed to read ESF_GZ_VSEC_TBL_BAR, rc=%d\n",
			  rc);
		वापस rc;
	पूर्ण

	अगर (bar == ESE_GZ_CFGBAR_CONT_CAP_BAR_NUM_EXPANSION_ROM ||
	    bar == ESE_GZ_CFGBAR_CONT_CAP_BAR_NUM_INVALID) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Bad BAR value of %d in Xilinx capabilities sub-table.\n",
			  bar);
		वापस -EINVAL;
	पूर्ण

	rc = ef100_pci_get_config_bits(efx, vndr_cap, TBL_OFF_LO, &offset_lo);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Failed to read ESF_GZ_VSEC_TBL_OFF_LO, rc=%d\n",
			  rc);
		वापस rc;
	पूर्ण

	/* Get optional extension to 64bit offset. */
	अगर (has_offset_hi) अणु
		rc = ef100_pci_get_config_bits(efx, vndr_cap, TBL_OFF_HI, &offset_high);
		अगर (rc) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Failed to read ESF_GZ_VSEC_TBL_OFF_HI, rc=%d\n",
				  rc);
			वापस rc;
		पूर्ण
	पूर्ण

	offset = (((u64)offset_lo) << ESE_GZ_VSEC_TBL_OFF_LO_BYTES_SHIFT) |
		 (((u64)offset_high) << ESE_GZ_VSEC_TBL_OFF_HI_BYTES_SHIFT);

	अगर (offset > pci_resource_len(efx->pci_dev, bar) - माप(u32) * 2) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Xilinx table will overrun BAR[%d] offset=0x%llx\n",
			  bar, offset);
		वापस -EINVAL;
	पूर्ण

	/* Temporarily map BAR. */
	rc = efx_init_io(efx, bar,
			 (dma_addr_t)DMA_BIT_MASK(ESF_GZ_TX_SEND_ADDR_WIDTH),
			 pci_resource_len(efx->pci_dev, bar));
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "efx_init_io failed, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	rc = ef100_pci_walk_xilinx_table(efx, offset, result);

	/* Unmap temporarily mapped BAR. */
	efx_fini_io(efx);
	वापस rc;
पूर्ण

/* Call ef100_pci_parse_ef100_entry() क्रम each Xilinx PCI_EXT_CAP_ID_VNDR
 * capability.
 */
अटल पूर्णांक ef100_pci_find_func_ctrl_winकरोw(काष्ठा efx_nic *efx,
					   काष्ठा ef100_func_ctl_winकरोw *result)
अणु
	पूर्णांक num_xilinx_caps = 0;
	पूर्णांक cap = 0;

	result->valid = false;

	जबतक ((cap = pci_find_next_ext_capability(efx->pci_dev, cap, PCI_EXT_CAP_ID_VNDR)) != 0) अणु
		पूर्णांक vndr_cap = cap + PCI_EXT_CAP_HDR_LENGTH;
		u32 vsec_ver = 0;
		u32 vsec_len = 0;
		u32 vsec_id = 0;
		पूर्णांक rc = 0;

		num_xilinx_caps++;

		rc = ef100_pci_get_config_bits(efx, vndr_cap, ID, &vsec_id);
		अगर (rc) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Failed to read ESF_GZ_VSEC_ID, rc=%d\n",
				  rc);
			वापस rc;
		पूर्ण

		rc = ef100_pci_get_config_bits(efx, vndr_cap, VER, &vsec_ver);
		अगर (rc) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Failed to read ESF_GZ_VSEC_VER, rc=%d\n",
				  rc);
			वापस rc;
		पूर्ण

		/* Get length of whole capability - i.e. starting at cap */
		rc = ef100_pci_get_config_bits(efx, vndr_cap, LEN, &vsec_len);
		अगर (rc) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Failed to read ESF_GZ_VSEC_LEN, rc=%d\n",
				  rc);
			वापस rc;
		पूर्ण

		अगर (vsec_id == ESE_GZ_XILINX_VSEC_ID &&
		    vsec_ver == ESE_GZ_VSEC_VER_XIL_CFGBAR &&
		    vsec_len >= ESE_GZ_VSEC_LEN_MIN) अणु
			bool has_offset_hi = (vsec_len >= ESE_GZ_VSEC_LEN_HIGH_OFFT);

			rc = ef100_pci_parse_xilinx_cap(efx, vndr_cap,
							has_offset_hi, result);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	अगर (num_xilinx_caps && !result->valid) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Seen %d Xilinx tables, but no EF100 entry.\n",
			  num_xilinx_caps);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Final NIC shutकरोwn
 * This is called only at module unload (or hotplug removal).  A PF can call
 * this on its VFs to ensure they are unbound first.
 */
अटल व्योम ef100_pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा efx_nic *efx;

	efx = pci_get_drvdata(pci_dev);
	अगर (!efx)
		वापस;

	rtnl_lock();
	dev_बंद(efx->net_dev);
	rtnl_unlock();

	/* Unरेजिस्टरing our netdev notअगरier triggers unbinding of TC indirect
	 * blocks, so we have to करो it beक्रमe PCI removal.
	 */
	unरेजिस्टर_netdevice_notअगरier(&efx->netdev_notअगरier);
	ef100_हटाओ(efx);
	efx_fini_io(efx);
	netअगर_dbg(efx, drv, efx->net_dev, "shutdown successful\n");

	pci_set_drvdata(pci_dev, शून्य);
	efx_fini_काष्ठा(efx);
	मुक्त_netdev(efx->net_dev);

	pci_disable_pcie_error_reporting(pci_dev);
पूर्ण;

अटल पूर्णांक ef100_pci_probe(काष्ठा pci_dev *pci_dev,
			   स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा ef100_func_ctl_winकरोw fcw = अणु 0 पूर्ण;
	काष्ठा net_device *net_dev;
	काष्ठा efx_nic *efx;
	पूर्णांक rc;

	/* Allocate and initialise a काष्ठा net_device and काष्ठा efx_nic */
	net_dev = alloc_etherdev_mq(माप(*efx), EFX_MAX_CORE_TX_QUEUES);
	अगर (!net_dev)
		वापस -ENOMEM;
	efx = netdev_priv(net_dev);
	efx->type = (स्थिर काष्ठा efx_nic_type *)entry->driver_data;

	pci_set_drvdata(pci_dev, efx);
	SET_NETDEV_DEV(net_dev, &pci_dev->dev);
	rc = efx_init_काष्ठा(efx, pci_dev, net_dev);
	अगर (rc)
		जाओ fail;

	efx->vi_stride = EF100_DEFAULT_VI_STRIDE;
	netअगर_info(efx, probe, efx->net_dev,
		   "Solarflare EF100 NIC detected\n");

	rc = ef100_pci_find_func_ctrl_winकरोw(efx, &fcw);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Error looking for ef100 function control window, rc=%d\n",
			  rc);
		जाओ fail;
	पूर्ण

	अगर (!fcw.valid) अणु
		/* Extended capability not found - use शेषs. */
		fcw.bar = EFX_EF100_PCI_DEFAULT_BAR;
		fcw.offset = 0;
		fcw.valid = true;
	पूर्ण

	अगर (fcw.offset > pci_resource_len(efx->pci_dev, fcw.bar) - ESE_GZ_FCW_LEN) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Func control window overruns BAR\n");
		rc = -EIO;
		जाओ fail;
	पूर्ण

	/* Set up basic I/O (BAR mappings etc) */
	rc = efx_init_io(efx, fcw.bar,
			 (dma_addr_t)DMA_BIT_MASK(ESF_GZ_TX_SEND_ADDR_WIDTH),
			 pci_resource_len(efx->pci_dev, fcw.bar));
	अगर (rc)
		जाओ fail;

	efx->reg_base = fcw.offset;

	efx->netdev_notअगरier.notअगरier_call = ef100_netdev_event;
	rc = रेजिस्टर_netdevice_notअगरier(&efx->netdev_notअगरier);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Failed to register netdevice notifier, rc=%d\n", rc);
		जाओ fail;
	पूर्ण

	rc = efx->type->probe(efx);
	अगर (rc)
		जाओ fail;

	netअगर_dbg(efx, probe, efx->net_dev, "initialisation successful\n");

	वापस 0;

fail:
	ef100_pci_हटाओ(pci_dev);
	वापस rc;
पूर्ण

/* PCI device ID table */
अटल स्थिर काष्ठा pci_device_id ef100_pci_table[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_XILINX, 0x0100),  /* Riverhead PF */
		.driver_data = (अचिन्हित दीर्घ) &ef100_pf_nic_type पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_XILINX, 0x1100),  /* Riverhead VF */
		.driver_data = (अचिन्हित दीर्घ) &ef100_vf_nic_type पूर्ण,
	अणु0पूर्ण                     /* end of list */
पूर्ण;

काष्ठा pci_driver ef100_pci_driver = अणु
	.name           = "sfc_ef100",
	.id_table       = ef100_pci_table,
	.probe          = ef100_pci_probe,
	.हटाओ         = ef100_pci_हटाओ,
	.err_handler    = &efx_err_handlers,
पूर्ण;

MODULE_DEVICE_TABLE(pci, ef100_pci_table);
