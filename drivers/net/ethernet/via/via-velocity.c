<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This code is derived from the VIA reference driver (copyright message
 * below) provided to Red Hat by VIA Networking Technologies, Inc. क्रम
 * addition to the Linux kernel.
 *
 * The code has been merged पूर्णांकo one source file, cleaned up to follow
 * Linux coding style,  ported to the Linux 2.6 kernel tree and cleaned
 * क्रम 64bit hardware platक्रमms.
 *
 * TODO
 *	rx_copyअवरोध/alignment
 *	More testing
 *
 * The changes are (c) Copyright 2004, Red Hat Inc. <alan@lxorguk.ukuu.org.uk>
 * Additional fixes and clean up: Francois Romieu
 *
 * This source has not been verअगरied क्रम use in safety critical प्रणालीs.
 *
 * Please direct queries about the revamped driver to the linux-kernel
 * list not VIA.
 *
 * Original code:
 *
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * Author: Chuang Liang-Shing, AJ Jiang
 *
 * Date: Jan 24, 2003
 *
 * MODULE_LICENSE("GPL");
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <linux/पन.स>
#समावेश <linux/अगर.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <linux/crc32.h>

#समावेश "via-velocity.h"

क्रमागत velocity_bus_type अणु
	BUS_PCI,
	BUS_PLATFORM,
पूर्ण;

अटल पूर्णांक velocity_nics;

अटल व्योम velocity_set_घातer_state(काष्ठा velocity_info *vptr, अक्षर state)
अणु
	व्योम *addr = vptr->mac_regs;

	अगर (vptr->pdev)
		pci_set_घातer_state(vptr->pdev, state);
	अन्यथा
		ग_लिखोb(state, addr + 0x154);
पूर्ण

/**
 *	mac_get_cam_mask	-	Read a CAM mask
 *	@regs: रेजिस्टर block क्रम this velocity
 *	@mask: buffer to store mask
 *
 *	Fetch the mask bits of the selected CAM and store them पूर्णांकo the
 *	provided mask buffer.
 */
अटल व्योम mac_get_cam_mask(काष्ठा mac_regs __iomem *regs, u8 *mask)
अणु
	पूर्णांक i;

	/* Select CAM mask */
	BYTE_REG_BITS_SET(CAMCR_PS_CAM_MASK, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);

	ग_लिखोb(0, &regs->CAMADDR);

	/* पढ़ो mask */
	क्रम (i = 0; i < 8; i++)
		*mask++ = पढ़ोb(&(regs->MARCAM[i]));

	/* disable CAMEN */
	ग_लिखोb(0, &regs->CAMADDR);

	/* Select mar */
	BYTE_REG_BITS_SET(CAMCR_PS_MAR, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);
पूर्ण

/**
 *	mac_set_cam_mask	-	Set a CAM mask
 *	@regs: रेजिस्टर block क्रम this velocity
 *	@mask: CAM mask to load
 *
 *	Store a new mask पूर्णांकo a CAM
 */
अटल व्योम mac_set_cam_mask(काष्ठा mac_regs __iomem *regs, u8 *mask)
अणु
	पूर्णांक i;
	/* Select CAM mask */
	BYTE_REG_BITS_SET(CAMCR_PS_CAM_MASK, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);

	ग_लिखोb(CAMADDR_CAMEN, &regs->CAMADDR);

	क्रम (i = 0; i < 8; i++)
		ग_लिखोb(*mask++, &(regs->MARCAM[i]));

	/* disable CAMEN */
	ग_लिखोb(0, &regs->CAMADDR);

	/* Select mar */
	BYTE_REG_BITS_SET(CAMCR_PS_MAR, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);
पूर्ण

अटल व्योम mac_set_vlan_cam_mask(काष्ठा mac_regs __iomem *regs, u8 *mask)
अणु
	पूर्णांक i;
	/* Select CAM mask */
	BYTE_REG_BITS_SET(CAMCR_PS_CAM_MASK, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);

	ग_लिखोb(CAMADDR_CAMEN | CAMADDR_VCAMSL, &regs->CAMADDR);

	क्रम (i = 0; i < 8; i++)
		ग_लिखोb(*mask++, &(regs->MARCAM[i]));

	/* disable CAMEN */
	ग_लिखोb(0, &regs->CAMADDR);

	/* Select mar */
	BYTE_REG_BITS_SET(CAMCR_PS_MAR, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);
पूर्ण

/**
 *	mac_set_cam	-	set CAM data
 *	@regs: रेजिस्टर block of this velocity
 *	@idx: Cam index
 *	@addr: 2 or 6 bytes of CAM data
 *
 *	Load an address or vlan tag पूर्णांकo a CAM
 */
अटल व्योम mac_set_cam(काष्ठा mac_regs __iomem *regs, पूर्णांक idx, स्थिर u8 *addr)
अणु
	पूर्णांक i;

	/* Select CAM mask */
	BYTE_REG_BITS_SET(CAMCR_PS_CAM_DATA, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);

	idx &= (64 - 1);

	ग_लिखोb(CAMADDR_CAMEN | idx, &regs->CAMADDR);

	क्रम (i = 0; i < 6; i++)
		ग_लिखोb(*addr++, &(regs->MARCAM[i]));

	BYTE_REG_BITS_ON(CAMCR_CAMWR, &regs->CAMCR);

	udelay(10);

	ग_लिखोb(0, &regs->CAMADDR);

	/* Select mar */
	BYTE_REG_BITS_SET(CAMCR_PS_MAR, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);
पूर्ण

अटल व्योम mac_set_vlan_cam(काष्ठा mac_regs __iomem *regs, पूर्णांक idx,
			     स्थिर u8 *addr)
अणु

	/* Select CAM mask */
	BYTE_REG_BITS_SET(CAMCR_PS_CAM_DATA, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);

	idx &= (64 - 1);

	ग_लिखोb(CAMADDR_CAMEN | CAMADDR_VCAMSL | idx, &regs->CAMADDR);
	ग_लिखोw(*((u16 *) addr), &regs->MARCAM[0]);

	BYTE_REG_BITS_ON(CAMCR_CAMWR, &regs->CAMCR);

	udelay(10);

	ग_लिखोb(0, &regs->CAMADDR);

	/* Select mar */
	BYTE_REG_BITS_SET(CAMCR_PS_MAR, CAMCR_PS1 | CAMCR_PS0, &regs->CAMCR);
पूर्ण


/**
 *	mac_wol_reset	-	reset WOL after निकासing low घातer
 *	@regs: रेजिस्टर block of this velocity
 *
 *	Called after we drop out of wake on lan mode in order to
 *	reset the Wake on lan features. This function करोesn't restore
 *	the rest of the logic from the result of sleep/wakeup
 */
अटल व्योम mac_wol_reset(काष्ठा mac_regs __iomem *regs)
अणु

	/* Turn off SWPTAG right after leaving घातer mode */
	BYTE_REG_BITS_OFF(STICKHW_SWPTAG, &regs->STICKHW);
	/* clear sticky bits */
	BYTE_REG_BITS_OFF((STICKHW_DS1 | STICKHW_DS0), &regs->STICKHW);

	BYTE_REG_BITS_OFF(CHIPGCR_FCGMII, &regs->CHIPGCR);
	BYTE_REG_BITS_OFF(CHIPGCR_FCMODE, &regs->CHIPGCR);
	/* disable क्रमce PME-enable */
	ग_लिखोb(WOLCFG_PMEOVR, &regs->WOLCFGClr);
	/* disable घातer-event config bit */
	ग_लिखोw(0xFFFF, &regs->WOLCRClr);
	/* clear घातer status */
	ग_लिखोw(0xFFFF, &regs->WOLSRClr);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops velocity_ethtool_ops;

/*
    Define module options
*/

MODULE_AUTHOR("VIA Networking Technologies, Inc.");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VIA Networking Velocity Family Gigabit Ethernet Adapter Driver");

#घोषणा VELOCITY_PARAM(N, D) \
	अटल पूर्णांक N[MAX_UNITS] = OPTION_DEFAULT;\
	module_param_array(N, पूर्णांक, शून्य, 0); \
	MODULE_PARM_DESC(N, D);

#घोषणा RX_DESC_MIN     64
#घोषणा RX_DESC_MAX     255
#घोषणा RX_DESC_DEF     64
VELOCITY_PARAM(RxDescriptors, "Number of receive descriptors");

#घोषणा TX_DESC_MIN     16
#घोषणा TX_DESC_MAX     256
#घोषणा TX_DESC_DEF     64
VELOCITY_PARAM(TxDescriptors, "Number of transmit descriptors");

#घोषणा RX_THRESH_MIN   0
#घोषणा RX_THRESH_MAX   3
#घोषणा RX_THRESH_DEF   0
/* rx_thresh[] is used क्रम controlling the receive fअगरo threshold.
   0: indicate the rxfअगरo threshold is 128 bytes.
   1: indicate the rxfअगरo threshold is 512 bytes.
   2: indicate the rxfअगरo threshold is 1024 bytes.
   3: indicate the rxfअगरo threshold is store & क्रमward.
*/
VELOCITY_PARAM(rx_thresh, "Receive fifo threshold");

#घोषणा DMA_LENGTH_MIN  0
#घोषणा DMA_LENGTH_MAX  7
#घोषणा DMA_LENGTH_DEF  6

/* DMA_length[] is used क्रम controlling the DMA length
   0: 8 DWORDs
   1: 16 DWORDs
   2: 32 DWORDs
   3: 64 DWORDs
   4: 128 DWORDs
   5: 256 DWORDs
   6: SF(flush till emply)
   7: SF(flush till emply)
*/
VELOCITY_PARAM(DMA_length, "DMA length");

#घोषणा IP_ALIG_DEF     0
/* IP_byte_align[] is used क्रम IP header DWORD byte aligned
   0: indicate the IP header won't be DWORD byte aligned.(Default) .
   1: indicate the IP header will be DWORD byte aligned.
      In some environment, the IP header should be DWORD byte aligned,
      or the packet will be droped when we receive it. (eg: IPVS)
*/
VELOCITY_PARAM(IP_byte_align, "Enable IP header dword aligned");

#घोषणा FLOW_CNTL_DEF   1
#घोषणा FLOW_CNTL_MIN   1
#घोषणा FLOW_CNTL_MAX   5

/* flow_control[] is used क्रम setting the flow control ability of NIC.
   1: hardware deafult - AUTO (शेष). Use Hardware शेष value in ANAR.
   2: enable TX flow control.
   3: enable RX flow control.
   4: enable RX/TX flow control.
   5: disable
*/
VELOCITY_PARAM(flow_control, "Enable flow control ability");

#घोषणा MED_LNK_DEF 0
#घोषणा MED_LNK_MIN 0
#घोषणा MED_LNK_MAX 5
/* speed_duplex[] is used क्रम setting the speed and duplex mode of NIC.
   0: indicate स्वतःnegotiation क्रम both speed and duplex mode
   1: indicate 100Mbps half duplex mode
   2: indicate 100Mbps full duplex mode
   3: indicate 10Mbps half duplex mode
   4: indicate 10Mbps full duplex mode
   5: indicate 1000Mbps full duplex mode

   Note:
   अगर EEPROM have been set to the क्रमce mode, this option is ignored
   by driver.
*/
VELOCITY_PARAM(speed_duplex, "Setting the speed and duplex mode");

#घोषणा WOL_OPT_DEF     0
#घोषणा WOL_OPT_MIN     0
#घोषणा WOL_OPT_MAX     7
/* wol_opts[] is used क्रम controlling wake on lan behavior.
   0: Wake up अगर recevied a magic packet. (Default)
   1: Wake up अगर link status is on/off.
   2: Wake up अगर recevied an arp packet.
   4: Wake up अगर recevied any unicast packet.
   Those value can be sumed up to support more than one option.
*/
VELOCITY_PARAM(wol_opts, "Wake On Lan options");

अटल पूर्णांक rx_copyअवरोध = 200;
module_param(rx_copyअवरोध, पूर्णांक, 0644);
MODULE_PARM_DESC(rx_copyअवरोध, "Copy breakpoint for copy-only-tiny-frames");

/*
 *	Internal board variants. At the moment we have only one
 */
अटल काष्ठा velocity_info_tbl chip_info_table[] = अणु
	अणुCHIP_TYPE_VT6110, "VIA Networking Velocity Family Gigabit Ethernet Adapter", 1, 0x00FFFFFFULपूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 *	Describe the PCI device identअगरiers that we support in this
 *	device driver. Used क्रम hotplug स्वतःloading.
 */

अटल स्थिर काष्ठा pci_device_id velocity_pci_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_612X) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, velocity_pci_id_table);

/*
 *	Describe the OF device identअगरiers that we support in this
 *	device driver. Used क्रम devicetree nodes.
 */
अटल स्थिर काष्ठा of_device_id velocity_of_ids[] = अणु
	अणु .compatible = "via,velocity-vt6110", .data = &chip_info_table[0] पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, velocity_of_ids);

/**
 *	get_chip_name	- 	identअगरier to name
 *	@chip_id: chip identअगरier
 *
 *	Given a chip identअगरier वापस a suitable description. Returns
 *	a poपूर्णांकer a अटल string valid जबतक the driver is loaded.
 */
अटल स्थिर अक्षर *get_chip_name(क्रमागत chip_type chip_id)
अणु
	पूर्णांक i;
	क्रम (i = 0; chip_info_table[i].name != शून्य; i++)
		अगर (chip_info_table[i].chip_id == chip_id)
			अवरोध;
	वापस chip_info_table[i].name;
पूर्ण

/**
 *	velocity_set_पूर्णांक_opt	-	parser क्रम पूर्णांकeger options
 *	@opt: poपूर्णांकer to option value
 *	@val: value the user requested (or -1 क्रम शेष)
 *	@min: lowest value allowed
 *	@max: highest value allowed
 *	@def: शेष value
 *	@name: property name
 *
 *	Set an पूर्णांकeger property in the module options. This function करोes
 *	all the verअगरication and checking as well as reporting so that
 *	we करोn't duplicate code क्रम each option.
 */
अटल व्योम velocity_set_पूर्णांक_opt(पूर्णांक *opt, पूर्णांक val, पूर्णांक min, पूर्णांक max, पूर्णांक def,
				 अक्षर *name)
अणु
	अगर (val == -1)
		*opt = def;
	अन्यथा अगर (val < min || val > max) अणु
		pr_notice("the value of parameter %s is invalid, the valid range is (%d-%d)\n",
			  name, min, max);
		*opt = def;
	पूर्ण अन्यथा अणु
		pr_info("set value of parameter %s to %d\n", name, val);
		*opt = val;
	पूर्ण
पूर्ण

/**
 *	velocity_set_bool_opt	-	parser क्रम boolean options
 *	@opt: poपूर्णांकer to option value
 *	@val: value the user requested (or -1 क्रम शेष)
 *	@def: शेष value (yes/no)
 *	@flag: numeric value to set क्रम true.
 *	@name: property name
 *
 *	Set a boolean property in the module options. This function करोes
 *	all the verअगरication and checking as well as reporting so that
 *	we करोn't duplicate code क्रम each option.
 */
अटल व्योम velocity_set_bool_opt(u32 *opt, पूर्णांक val, पूर्णांक def, u32 flag,
				  अक्षर *name)
अणु
	(*opt) &= (~flag);
	अगर (val == -1)
		*opt |= (def ? flag : 0);
	अन्यथा अगर (val < 0 || val > 1) अणु
		pr_notice("the value of parameter %s is invalid, the valid range is (%d-%d)\n",
			  name, 0, 1);
		*opt |= (def ? flag : 0);
	पूर्ण अन्यथा अणु
		pr_info("set parameter %s to %s\n",
			name, val ? "TRUE" : "FALSE");
		*opt |= (val ? flag : 0);
	पूर्ण
पूर्ण

/**
 *	velocity_get_options	-	set options on device
 *	@opts: option काष्ठाure क्रम the device
 *	@index: index of option to use in module options array
 *
 *	Turn the module and command options पूर्णांकo a single काष्ठाure
 *	क्रम the current device
 */
अटल व्योम velocity_get_options(काष्ठा velocity_opt *opts, पूर्णांक index)
अणु

	velocity_set_पूर्णांक_opt(&opts->rx_thresh, rx_thresh[index],
			     RX_THRESH_MIN, RX_THRESH_MAX, RX_THRESH_DEF,
			     "rx_thresh");
	velocity_set_पूर्णांक_opt(&opts->DMA_length, DMA_length[index],
			     DMA_LENGTH_MIN, DMA_LENGTH_MAX, DMA_LENGTH_DEF,
			     "DMA_length");
	velocity_set_पूर्णांक_opt(&opts->numrx, RxDescriptors[index],
			     RX_DESC_MIN, RX_DESC_MAX, RX_DESC_DEF,
			     "RxDescriptors");
	velocity_set_पूर्णांक_opt(&opts->numtx, TxDescriptors[index],
			     TX_DESC_MIN, TX_DESC_MAX, TX_DESC_DEF,
			     "TxDescriptors");

	velocity_set_पूर्णांक_opt(&opts->flow_cntl, flow_control[index],
			     FLOW_CNTL_MIN, FLOW_CNTL_MAX, FLOW_CNTL_DEF,
			     "flow_control");
	velocity_set_bool_opt(&opts->flags, IP_byte_align[index],
			      IP_ALIG_DEF, VELOCITY_FLAGS_IP_ALIGN,
			      "IP_byte_align");
	velocity_set_पूर्णांक_opt((पूर्णांक *) &opts->spd_dpx, speed_duplex[index],
			     MED_LNK_MIN, MED_LNK_MAX, MED_LNK_DEF,
			     "Media link mode");
	velocity_set_पूर्णांक_opt(&opts->wol_opts, wol_opts[index],
			     WOL_OPT_MIN, WOL_OPT_MAX, WOL_OPT_DEF,
			     "Wake On Lan options");
	opts->numrx = (opts->numrx & ~3);
पूर्ण

/**
 *	velocity_init_cam_filter	-	initialise CAM
 *	@vptr: velocity to program
 *
 *	Initialize the content addressable memory used क्रम filters. Load
 *	appropriately according to the presence of VLAN
 */
अटल व्योम velocity_init_cam_filter(काष्ठा velocity_info *vptr)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	अचिन्हित पूर्णांक vid, i = 0;

	/* Turn on MCFG_PQEN, turn off MCFG_RTGOPT */
	WORD_REG_BITS_SET(MCFG_PQEN, MCFG_RTGOPT, &regs->MCFG);
	WORD_REG_BITS_ON(MCFG_VIDFR, &regs->MCFG);

	/* Disable all CAMs */
	स_रखो(vptr->vCAMmask, 0, माप(u8) * 8);
	स_रखो(vptr->mCAMmask, 0, माप(u8) * 8);
	mac_set_vlan_cam_mask(regs, vptr->vCAMmask);
	mac_set_cam_mask(regs, vptr->mCAMmask);

	/* Enable VCAMs */
	क्रम_each_set_bit(vid, vptr->active_vlans, VLAN_N_VID) अणु
		mac_set_vlan_cam(regs, i, (u8 *) &vid);
		vptr->vCAMmask[i / 8] |= 0x1 << (i % 8);
		अगर (++i >= VCAM_SIZE)
			अवरोध;
	पूर्ण
	mac_set_vlan_cam_mask(regs, vptr->vCAMmask);
पूर्ण

अटल पूर्णांक velocity_vlan_rx_add_vid(काष्ठा net_device *dev,
				    __be16 proto, u16 vid)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	spin_lock_irq(&vptr->lock);
	set_bit(vid, vptr->active_vlans);
	velocity_init_cam_filter(vptr);
	spin_unlock_irq(&vptr->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक velocity_vlan_rx_समाप्त_vid(काष्ठा net_device *dev,
				     __be16 proto, u16 vid)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	spin_lock_irq(&vptr->lock);
	clear_bit(vid, vptr->active_vlans);
	velocity_init_cam_filter(vptr);
	spin_unlock_irq(&vptr->lock);
	वापस 0;
पूर्ण

अटल व्योम velocity_init_rx_ring_indexes(काष्ठा velocity_info *vptr)
अणु
	vptr->rx.dirty = vptr->rx.filled = vptr->rx.curr = 0;
पूर्ण

/**
 *	velocity_rx_reset	-	handle a receive reset
 *	@vptr: velocity we are resetting
 *
 *	Reset the ownership and status क्रम the receive ring side.
 *	Hand all the receive queue to the NIC.
 */
अटल व्योम velocity_rx_reset(काष्ठा velocity_info *vptr)
अणु

	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	पूर्णांक i;

	velocity_init_rx_ring_indexes(vptr);

	/*
	 *	Init state, all RD entries beदीर्घ to the NIC
	 */
	क्रम (i = 0; i < vptr->options.numrx; ++i)
		vptr->rx.ring[i].rdesc0.len |= OWNED_BY_NIC;

	ग_लिखोw(vptr->options.numrx, &regs->RBRDU);
	ग_लिखोl(vptr->rx.pool_dma, &regs->RDBaseLo);
	ग_लिखोw(0, &regs->RDIdx);
	ग_लिखोw(vptr->options.numrx - 1, &regs->RDCSize);
पूर्ण

/**
 *	velocity_get_opt_media_mode	-	get media selection
 *	@vptr: velocity adapter
 *
 *	Get the media mode stored in EEPROM or module options and load
 *	mii_status accordingly. The requested link state inक्रमmation
 *	is also वापसed.
 */
अटल u32 velocity_get_opt_media_mode(काष्ठा velocity_info *vptr)
अणु
	u32 status = 0;

	चयन (vptr->options.spd_dpx) अणु
	हाल SPD_DPX_AUTO:
		status = VELOCITY_AUTONEG_ENABLE;
		अवरोध;
	हाल SPD_DPX_100_FULL:
		status = VELOCITY_SPEED_100 | VELOCITY_DUPLEX_FULL;
		अवरोध;
	हाल SPD_DPX_10_FULL:
		status = VELOCITY_SPEED_10 | VELOCITY_DUPLEX_FULL;
		अवरोध;
	हाल SPD_DPX_100_HALF:
		status = VELOCITY_SPEED_100;
		अवरोध;
	हाल SPD_DPX_10_HALF:
		status = VELOCITY_SPEED_10;
		अवरोध;
	हाल SPD_DPX_1000_FULL:
		status = VELOCITY_SPEED_1000 | VELOCITY_DUPLEX_FULL;
		अवरोध;
	पूर्ण
	vptr->mii_status = status;
	वापस status;
पूर्ण

/**
 *	safe_disable_mii_स्वतःpoll	-	स्वतःpoll off
 *	@regs: velocity रेजिस्टरs
 *
 *	Turn off the स्वतःpoll and रुको क्रम it to disable on the chip
 */
अटल व्योम safe_disable_mii_स्वतःpoll(काष्ठा mac_regs __iomem *regs)
अणु
	u16 ww;

	/*  turn off MAUTO */
	ग_लिखोb(0, &regs->MIICR);
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		udelay(1);
		अगर (BYTE_REG_BITS_IS_ON(MIISR_MIDLE, &regs->MIISR))
			अवरोध;
	पूर्ण
पूर्ण

/**
 *	enable_mii_स्वतःpoll	-	turn on स्वतःpolling
 *	@regs: velocity रेजिस्टरs
 *
 *	Enable the MII link status स्वतःpoll feature on the Velocity
 *	hardware. Wait क्रम it to enable.
 */
अटल व्योम enable_mii_स्वतःpoll(काष्ठा mac_regs __iomem *regs)
अणु
	पूर्णांक ii;

	ग_लिखोb(0, &(regs->MIICR));
	ग_लिखोb(MIIADR_SWMPL, &regs->MIIADR);

	क्रम (ii = 0; ii < W_MAX_TIMEOUT; ii++) अणु
		udelay(1);
		अगर (BYTE_REG_BITS_IS_ON(MIISR_MIDLE, &regs->MIISR))
			अवरोध;
	पूर्ण

	ग_लिखोb(MIICR_MAUTO, &regs->MIICR);

	क्रम (ii = 0; ii < W_MAX_TIMEOUT; ii++) अणु
		udelay(1);
		अगर (!BYTE_REG_BITS_IS_ON(MIISR_MIDLE, &regs->MIISR))
			अवरोध;
	पूर्ण

पूर्ण

/**
 *	velocity_mii_पढ़ो	-	पढ़ो MII data
 *	@regs: velocity रेजिस्टरs
 *	@index: MII रेजिस्टर index
 *	@data: buffer क्रम received data
 *
 *	Perक्रमm a single पढ़ो of an MII 16bit रेजिस्टर. Returns zero
 *	on success or -ETIMEDOUT अगर the PHY did not respond.
 */
अटल पूर्णांक velocity_mii_पढ़ो(काष्ठा mac_regs __iomem *regs, u8 index, u16 *data)
अणु
	u16 ww;

	/*
	 *	Disable MIICR_MAUTO, so that mii addr can be set normally
	 */
	safe_disable_mii_स्वतःpoll(regs);

	ग_लिखोb(index, &regs->MIIADR);

	BYTE_REG_BITS_ON(MIICR_RCMD, &regs->MIICR);

	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(पढ़ोb(&regs->MIICR) & MIICR_RCMD))
			अवरोध;
	पूर्ण

	*data = पढ़ोw(&regs->MIIDATA);

	enable_mii_स्वतःpoll(regs);
	अगर (ww == W_MAX_TIMEOUT)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

/**
 *	mii_check_media_mode	-	check media state
 *	@regs: velocity रेजिस्टरs
 *
 *	Check the current MII status and determine the link status
 *	accordingly
 */
अटल u32 mii_check_media_mode(काष्ठा mac_regs __iomem *regs)
अणु
	u32 status = 0;
	u16 ANAR;

	अगर (!MII_REG_BITS_IS_ON(BMSR_LSTATUS, MII_BMSR, regs))
		status |= VELOCITY_LINK_FAIL;

	अगर (MII_REG_BITS_IS_ON(ADVERTISE_1000FULL, MII_CTRL1000, regs))
		status |= VELOCITY_SPEED_1000 | VELOCITY_DUPLEX_FULL;
	अन्यथा अगर (MII_REG_BITS_IS_ON(ADVERTISE_1000HALF, MII_CTRL1000, regs))
		status |= (VELOCITY_SPEED_1000);
	अन्यथा अणु
		velocity_mii_पढ़ो(regs, MII_ADVERTISE, &ANAR);
		अगर (ANAR & ADVERTISE_100FULL)
			status |= (VELOCITY_SPEED_100 | VELOCITY_DUPLEX_FULL);
		अन्यथा अगर (ANAR & ADVERTISE_100HALF)
			status |= VELOCITY_SPEED_100;
		अन्यथा अगर (ANAR & ADVERTISE_10FULL)
			status |= (VELOCITY_SPEED_10 | VELOCITY_DUPLEX_FULL);
		अन्यथा
			status |= (VELOCITY_SPEED_10);
	पूर्ण

	अगर (MII_REG_BITS_IS_ON(BMCR_ANENABLE, MII_BMCR, regs)) अणु
		velocity_mii_पढ़ो(regs, MII_ADVERTISE, &ANAR);
		अगर ((ANAR & (ADVERTISE_100FULL | ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF))
		    == (ADVERTISE_100FULL | ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF)) अणु
			अगर (MII_REG_BITS_IS_ON(ADVERTISE_1000HALF | ADVERTISE_1000FULL, MII_CTRL1000, regs))
				status |= VELOCITY_AUTONEG_ENABLE;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 *	velocity_mii_ग_लिखो	-	ग_लिखो MII data
 *	@regs: velocity रेजिस्टरs
 *	@mii_addr: MII रेजिस्टर index
 *	@data: 16bit data क्रम the MII रेजिस्टर
 *
 *	Perक्रमm a single ग_लिखो to an MII 16bit रेजिस्टर. Returns zero
 *	on success or -ETIMEDOUT अगर the PHY did not respond.
 */
अटल पूर्णांक velocity_mii_ग_लिखो(काष्ठा mac_regs __iomem *regs, u8 mii_addr, u16 data)
अणु
	u16 ww;

	/*
	 *	Disable MIICR_MAUTO, so that mii addr can be set normally
	 */
	safe_disable_mii_स्वतःpoll(regs);

	/* MII reg offset */
	ग_लिखोb(mii_addr, &regs->MIIADR);
	/* set MII data */
	ग_लिखोw(data, &regs->MIIDATA);

	/* turn on MIICR_WCMD */
	BYTE_REG_BITS_ON(MIICR_WCMD, &regs->MIICR);

	/* W_MAX_TIMEOUT is the समयout period */
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		udelay(5);
		अगर (!(पढ़ोb(&regs->MIICR) & MIICR_WCMD))
			अवरोध;
	पूर्ण
	enable_mii_स्वतःpoll(regs);

	अगर (ww == W_MAX_TIMEOUT)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

/**
 *	set_mii_flow_control	-	flow control setup
 *	@vptr: velocity पूर्णांकerface
 *
 *	Set up the flow control on this पूर्णांकerface according to
 *	the supplied user/eeprom options.
 */
अटल व्योम set_mii_flow_control(काष्ठा velocity_info *vptr)
अणु
	/*Enable or Disable PAUSE in ANAR */
	चयन (vptr->options.flow_cntl) अणु
	हाल FLOW_CNTL_TX:
		MII_REG_BITS_OFF(ADVERTISE_PAUSE_CAP, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_ON(ADVERTISE_PAUSE_ASYM, MII_ADVERTISE, vptr->mac_regs);
		अवरोध;

	हाल FLOW_CNTL_RX:
		MII_REG_BITS_ON(ADVERTISE_PAUSE_CAP, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_ON(ADVERTISE_PAUSE_ASYM, MII_ADVERTISE, vptr->mac_regs);
		अवरोध;

	हाल FLOW_CNTL_TX_RX:
		MII_REG_BITS_ON(ADVERTISE_PAUSE_CAP, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_OFF(ADVERTISE_PAUSE_ASYM, MII_ADVERTISE, vptr->mac_regs);
		अवरोध;

	हाल FLOW_CNTL_DISABLE:
		MII_REG_BITS_OFF(ADVERTISE_PAUSE_CAP, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_OFF(ADVERTISE_PAUSE_ASYM, MII_ADVERTISE, vptr->mac_regs);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	mii_set_स्वतः_on		-	स्वतःnegotiate on
 *	@vptr: velocity
 *
 *	Enable स्वतःnegotation on this पूर्णांकerface
 */
अटल व्योम mii_set_स्वतः_on(काष्ठा velocity_info *vptr)
अणु
	अगर (MII_REG_BITS_IS_ON(BMCR_ANENABLE, MII_BMCR, vptr->mac_regs))
		MII_REG_BITS_ON(BMCR_ANRESTART, MII_BMCR, vptr->mac_regs);
	अन्यथा
		MII_REG_BITS_ON(BMCR_ANENABLE, MII_BMCR, vptr->mac_regs);
पूर्ण

अटल u32 check_connection_type(काष्ठा mac_regs __iomem *regs)
अणु
	u32 status = 0;
	u8 PHYSR0;
	u16 ANAR;
	PHYSR0 = पढ़ोb(&regs->PHYSR0);

	/*
	   अगर (!(PHYSR0 & PHYSR0_LINKGD))
	   status|=VELOCITY_LINK_FAIL;
	 */

	अगर (PHYSR0 & PHYSR0_FDPX)
		status |= VELOCITY_DUPLEX_FULL;

	अगर (PHYSR0 & PHYSR0_SPDG)
		status |= VELOCITY_SPEED_1000;
	अन्यथा अगर (PHYSR0 & PHYSR0_SPD10)
		status |= VELOCITY_SPEED_10;
	अन्यथा
		status |= VELOCITY_SPEED_100;

	अगर (MII_REG_BITS_IS_ON(BMCR_ANENABLE, MII_BMCR, regs)) अणु
		velocity_mii_पढ़ो(regs, MII_ADVERTISE, &ANAR);
		अगर ((ANAR & (ADVERTISE_100FULL | ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF))
		    == (ADVERTISE_100FULL | ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF)) अणु
			अगर (MII_REG_BITS_IS_ON(ADVERTISE_1000HALF | ADVERTISE_1000FULL, MII_CTRL1000, regs))
				status |= VELOCITY_AUTONEG_ENABLE;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 *	velocity_set_media_mode		-	set media mode
 *	@vptr: velocity adapter
 *	@mii_status: old MII link state
 *
 *	Check the media link state and configure the flow control
 *	PHY and also velocity hardware setup accordingly. In particular
 *	we need to set up CD polling and frame bursting.
 */
अटल पूर्णांक velocity_set_media_mode(काष्ठा velocity_info *vptr, u32 mii_status)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;

	vptr->mii_status = mii_check_media_mode(vptr->mac_regs);

	/* Set mii link status */
	set_mii_flow_control(vptr);

	अगर (PHYID_GET_PHY_ID(vptr->phy_id) == PHYID_CICADA_CS8201)
		MII_REG_BITS_ON(AUXCR_MDPPS, MII_NCONFIG, vptr->mac_regs);

	/*
	 *	If connection type is AUTO
	 */
	अगर (mii_status & VELOCITY_AUTONEG_ENABLE) अणु
		netdev_info(vptr->netdev, "Velocity is in AUTO mode\n");
		/* clear क्रमce MAC mode bit */
		BYTE_REG_BITS_OFF(CHIPGCR_FCMODE, &regs->CHIPGCR);
		/* set duplex mode of MAC according to duplex mode of MII */
		MII_REG_BITS_ON(ADVERTISE_100FULL | ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_ON(ADVERTISE_1000FULL | ADVERTISE_1000HALF, MII_CTRL1000, vptr->mac_regs);
		MII_REG_BITS_ON(BMCR_SPEED1000, MII_BMCR, vptr->mac_regs);

		/* enable AUTO-NEGO mode */
		mii_set_स्वतः_on(vptr);
	पूर्ण अन्यथा अणु
		u16 CTRL1000;
		u16 ANAR;
		u8 CHIPGCR;

		/*
		 * 1. अगर it's 3119, disable frame bursting in halfduplex mode
		 *    and enable it in fullduplex mode
		 * 2. set correct MII/GMII and half/full duplex mode in CHIPGCR
		 * 3. only enable CD heart beat counter in 10HD mode
		 */

		/* set क्रमce MAC mode bit */
		BYTE_REG_BITS_ON(CHIPGCR_FCMODE, &regs->CHIPGCR);

		CHIPGCR = पढ़ोb(&regs->CHIPGCR);

		अगर (mii_status & VELOCITY_SPEED_1000)
			CHIPGCR |= CHIPGCR_FCGMII;
		अन्यथा
			CHIPGCR &= ~CHIPGCR_FCGMII;

		अगर (mii_status & VELOCITY_DUPLEX_FULL) अणु
			CHIPGCR |= CHIPGCR_FCFDX;
			ग_लिखोb(CHIPGCR, &regs->CHIPGCR);
			netdev_info(vptr->netdev,
				    "set Velocity to forced full mode\n");
			अगर (vptr->rev_id < REV_ID_VT3216_A0)
				BYTE_REG_BITS_OFF(TCR_TB2BDIS, &regs->TCR);
		पूर्ण अन्यथा अणु
			CHIPGCR &= ~CHIPGCR_FCFDX;
			netdev_info(vptr->netdev,
				    "set Velocity to forced half mode\n");
			ग_लिखोb(CHIPGCR, &regs->CHIPGCR);
			अगर (vptr->rev_id < REV_ID_VT3216_A0)
				BYTE_REG_BITS_ON(TCR_TB2BDIS, &regs->TCR);
		पूर्ण

		velocity_mii_पढ़ो(vptr->mac_regs, MII_CTRL1000, &CTRL1000);
		CTRL1000 &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);
		अगर ((mii_status & VELOCITY_SPEED_1000) &&
		    (mii_status & VELOCITY_DUPLEX_FULL)) अणु
			CTRL1000 |= ADVERTISE_1000FULL;
		पूर्ण
		velocity_mii_ग_लिखो(vptr->mac_regs, MII_CTRL1000, CTRL1000);

		अगर (!(mii_status & VELOCITY_DUPLEX_FULL) && (mii_status & VELOCITY_SPEED_10))
			BYTE_REG_BITS_OFF(TESTCFG_HBDIS, &regs->TESTCFG);
		अन्यथा
			BYTE_REG_BITS_ON(TESTCFG_HBDIS, &regs->TESTCFG);

		/* MII_REG_BITS_OFF(BMCR_SPEED1000, MII_BMCR, vptr->mac_regs); */
		velocity_mii_पढ़ो(vptr->mac_regs, MII_ADVERTISE, &ANAR);
		ANAR &= (~(ADVERTISE_100FULL | ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF));
		अगर (mii_status & VELOCITY_SPEED_100) अणु
			अगर (mii_status & VELOCITY_DUPLEX_FULL)
				ANAR |= ADVERTISE_100FULL;
			अन्यथा
				ANAR |= ADVERTISE_100HALF;
		पूर्ण अन्यथा अगर (mii_status & VELOCITY_SPEED_10) अणु
			अगर (mii_status & VELOCITY_DUPLEX_FULL)
				ANAR |= ADVERTISE_10FULL;
			अन्यथा
				ANAR |= ADVERTISE_10HALF;
		पूर्ण
		velocity_mii_ग_लिखो(vptr->mac_regs, MII_ADVERTISE, ANAR);
		/* enable AUTO-NEGO mode */
		mii_set_स्वतः_on(vptr);
		/* MII_REG_BITS_ON(BMCR_ANENABLE, MII_BMCR, vptr->mac_regs); */
	पूर्ण
	/* vptr->mii_status=mii_check_media_mode(vptr->mac_regs); */
	/* vptr->mii_status=check_connection_type(vptr->mac_regs); */
	वापस VELOCITY_LINK_CHANGE;
पूर्ण

/**
 *	velocity_prपूर्णांक_link_status	-	link status reporting
 *	@vptr: velocity to report on
 *
 *	Turn the link status of the velocity card पूर्णांकo a kernel log
 *	description of the new link state, detailing speed and duplex
 *	status
 */
अटल व्योम velocity_prपूर्णांक_link_status(काष्ठा velocity_info *vptr)
अणु
	स्थिर अक्षर *link;
	स्थिर अक्षर *speed;
	स्थिर अक्षर *duplex;

	अगर (vptr->mii_status & VELOCITY_LINK_FAIL) अणु
		netdev_notice(vptr->netdev, "failed to detect cable link\n");
		वापस;
	पूर्ण

	अगर (vptr->options.spd_dpx == SPD_DPX_AUTO) अणु
		link = "auto-negotiation";

		अगर (vptr->mii_status & VELOCITY_SPEED_1000)
			speed = "1000";
		अन्यथा अगर (vptr->mii_status & VELOCITY_SPEED_100)
			speed = "100";
		अन्यथा
			speed = "10";

		अगर (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			duplex = "full";
		अन्यथा
			duplex = "half";
	पूर्ण अन्यथा अणु
		link = "forced";

		चयन (vptr->options.spd_dpx) अणु
		हाल SPD_DPX_1000_FULL:
			speed = "1000";
			duplex = "full";
			अवरोध;
		हाल SPD_DPX_100_HALF:
			speed = "100";
			duplex = "half";
			अवरोध;
		हाल SPD_DPX_100_FULL:
			speed = "100";
			duplex = "full";
			अवरोध;
		हाल SPD_DPX_10_HALF:
			speed = "10";
			duplex = "half";
			अवरोध;
		हाल SPD_DPX_10_FULL:
			speed = "10";
			duplex = "full";
			अवरोध;
		शेष:
			speed = "unknown";
			duplex = "unknown";
			अवरोध;
		पूर्ण
	पूर्ण
	netdev_notice(vptr->netdev, "Link %s speed %sM bps %s duplex\n",
		      link, speed, duplex);
पूर्ण

/**
 *	enable_flow_control_ability	-	flow control
 *	@vptr: veloity to configure
 *
 *	Set up flow control according to the flow control options
 *	determined by the eeprom/configuration.
 */
अटल व्योम enable_flow_control_ability(काष्ठा velocity_info *vptr)
अणु

	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;

	चयन (vptr->options.flow_cntl) अणु

	हाल FLOW_CNTL_DEFAULT:
		अगर (BYTE_REG_BITS_IS_ON(PHYSR0_RXFLC, &regs->PHYSR0))
			ग_लिखोl(CR0_FDXRFCEN, &regs->CR0Set);
		अन्यथा
			ग_लिखोl(CR0_FDXRFCEN, &regs->CR0Clr);

		अगर (BYTE_REG_BITS_IS_ON(PHYSR0_TXFLC, &regs->PHYSR0))
			ग_लिखोl(CR0_FDXTFCEN, &regs->CR0Set);
		अन्यथा
			ग_लिखोl(CR0_FDXTFCEN, &regs->CR0Clr);
		अवरोध;

	हाल FLOW_CNTL_TX:
		ग_लिखोl(CR0_FDXTFCEN, &regs->CR0Set);
		ग_लिखोl(CR0_FDXRFCEN, &regs->CR0Clr);
		अवरोध;

	हाल FLOW_CNTL_RX:
		ग_लिखोl(CR0_FDXRFCEN, &regs->CR0Set);
		ग_लिखोl(CR0_FDXTFCEN, &regs->CR0Clr);
		अवरोध;

	हाल FLOW_CNTL_TX_RX:
		ग_लिखोl(CR0_FDXTFCEN, &regs->CR0Set);
		ग_लिखोl(CR0_FDXRFCEN, &regs->CR0Set);
		अवरोध;

	हाल FLOW_CNTL_DISABLE:
		ग_लिखोl(CR0_FDXRFCEN, &regs->CR0Clr);
		ग_लिखोl(CR0_FDXTFCEN, &regs->CR0Clr);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

पूर्ण

/**
 *	velocity_soft_reset	-	soft reset
 *	@vptr: velocity to reset
 *
 *	Kick off a soft reset of the velocity adapter and then poll
 *	until the reset sequence has completed beक्रमe वापसing.
 */
अटल पूर्णांक velocity_soft_reset(काष्ठा velocity_info *vptr)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	पूर्णांक i = 0;

	ग_लिखोl(CR0_SFRST, &regs->CR0Set);

	क्रम (i = 0; i < W_MAX_TIMEOUT; i++) अणु
		udelay(5);
		अगर (!DWORD_REG_BITS_IS_ON(CR0_SFRST, &regs->CR0Set))
			अवरोध;
	पूर्ण

	अगर (i == W_MAX_TIMEOUT) अणु
		ग_लिखोl(CR0_FORSRST, &regs->CR0Set);
		/* FIXME: PCI POSTING */
		/* delay 2ms */
		mdelay(2);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	velocity_set_multi	-	filter list change callback
 *	@dev: network device
 *
 *	Called by the network layer when the filter lists need to change
 *	क्रम a velocity adapter. Reload the CAMs with the new address
 *	filter ruleset.
 */
अटल व्योम velocity_set_multi(काष्ठा net_device *dev)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	u8 rx_mode;
	पूर्णांक i;
	काष्ठा netdev_hw_addr *ha;

	अगर (dev->flags & IFF_PROMISC) अणु	/* Set promiscuous. */
		ग_लिखोl(0xffffffff, &regs->MARCAM[0]);
		ग_लिखोl(0xffffffff, &regs->MARCAM[4]);
		rx_mode = (RCR_AM | RCR_AB | RCR_PROM);
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > vptr->multicast_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		ग_लिखोl(0xffffffff, &regs->MARCAM[0]);
		ग_लिखोl(0xffffffff, &regs->MARCAM[4]);
		rx_mode = (RCR_AM | RCR_AB);
	पूर्ण अन्यथा अणु
		पूर्णांक offset = MCAM_SIZE - vptr->multicast_limit;
		mac_get_cam_mask(regs, vptr->mCAMmask);

		i = 0;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			mac_set_cam(regs, i + offset, ha->addr);
			vptr->mCAMmask[(offset + i) / 8] |= 1 << ((offset + i) & 7);
			i++;
		पूर्ण

		mac_set_cam_mask(regs, vptr->mCAMmask);
		rx_mode = RCR_AM | RCR_AB | RCR_AP;
	पूर्ण
	अगर (dev->mtu > 1500)
		rx_mode |= RCR_AL;

	BYTE_REG_BITS_ON(rx_mode, &regs->RCR);

पूर्ण

/*
 * MII access , media link mode setting functions
 */

/**
 *	mii_init	-	set up MII
 *	@vptr: velocity adapter
 *	@mii_status:  links tatus
 *
 *	Set up the PHY क्रम the current link state.
 */
अटल व्योम mii_init(काष्ठा velocity_info *vptr, u32 mii_status)
अणु
	u16 BMCR;

	चयन (PHYID_GET_PHY_ID(vptr->phy_id)) अणु
	हाल PHYID_ICPLUS_IP101A:
		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP),
						MII_ADVERTISE, vptr->mac_regs);
		अगर (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION,
								vptr->mac_regs);
		अन्यथा
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION,
								vptr->mac_regs);
		MII_REG_BITS_ON(PLED_LALBE, MII_TPISTATUS, vptr->mac_regs);
		अवरोध;
	हाल PHYID_CICADA_CS8201:
		/*
		 *	Reset to hardware शेष
		 */
		MII_REG_BITS_OFF((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);
		/*
		 *	Turn on ECHODIS bit in NWay-क्रमced full mode and turn it
		 *	off it in NWay-क्रमced half mode क्रम NWay-क्रमced v.s.
		 *	legacy-क्रमced issue.
		 */
		अगर (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		अन्यथा
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		/*
		 *	Turn on Link/Activity LED enable bit क्रम CIS8201
		 */
		MII_REG_BITS_ON(PLED_LALBE, MII_TPISTATUS, vptr->mac_regs);
		अवरोध;
	हाल PHYID_VT3216_32BIT:
	हाल PHYID_VT3216_64BIT:
		/*
		 *	Reset to hardware शेष
		 */
		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);
		/*
		 *	Turn on ECHODIS bit in NWay-क्रमced full mode and turn it
		 *	off it in NWay-क्रमced half mode क्रम NWay-क्रमced v.s.
		 *	legacy-क्रमced issue
		 */
		अगर (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		अन्यथा
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		अवरोध;

	हाल PHYID_MARVELL_1000:
	हाल PHYID_MARVELL_1000S:
		/*
		 *	Assert CRS on Transmit
		 */
		MII_REG_BITS_ON(PSCR_ACRSTX, MII_REG_PSCR, vptr->mac_regs);
		/*
		 *	Reset to hardware शेष
		 */
		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);
		अवरोध;
	शेष:
		;
	पूर्ण
	velocity_mii_पढ़ो(vptr->mac_regs, MII_BMCR, &BMCR);
	अगर (BMCR & BMCR_ISOLATE) अणु
		BMCR &= ~BMCR_ISOLATE;
		velocity_mii_ग_लिखो(vptr->mac_regs, MII_BMCR, BMCR);
	पूर्ण
पूर्ण

/**
 * setup_queue_समयrs	-	Setup पूर्णांकerrupt समयrs
 * @vptr: velocity adapter
 *
 * Setup पूर्णांकerrupt frequency during suppression (समयout अगर the frame
 * count isn't filled).
 */
अटल व्योम setup_queue_समयrs(काष्ठा velocity_info *vptr)
अणु
	/* Only क्रम newer revisions */
	अगर (vptr->rev_id >= REV_ID_VT3216_A0) अणु
		u8 txqueue_समयr = 0;
		u8 rxqueue_समयr = 0;

		अगर (vptr->mii_status & (VELOCITY_SPEED_1000 |
				VELOCITY_SPEED_100)) अणु
			txqueue_समयr = vptr->options.txqueue_समयr;
			rxqueue_समयr = vptr->options.rxqueue_समयr;
		पूर्ण

		ग_लिखोb(txqueue_समयr, &vptr->mac_regs->TQETMR);
		ग_लिखोb(rxqueue_समयr, &vptr->mac_regs->RQETMR);
	पूर्ण
पूर्ण

/**
 * setup_adaptive_पूर्णांकerrupts  -  Setup पूर्णांकerrupt suppression
 * @vptr: velocity adapter
 *
 * The velocity is able to suppress पूर्णांकerrupt during high पूर्णांकerrupt load.
 * This function turns on that feature.
 */
अटल व्योम setup_adaptive_पूर्णांकerrupts(काष्ठा velocity_info *vptr)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	u16 tx_पूर्णांकsup = vptr->options.tx_पूर्णांकsup;
	u16 rx_पूर्णांकsup = vptr->options.rx_पूर्णांकsup;

	/* Setup शेष पूर्णांकerrupt mask (will be changed below) */
	vptr->पूर्णांक_mask = INT_MASK_DEF;

	/* Set Tx Interrupt Suppression Threshold */
	ग_लिखोb(CAMCR_PS0, &regs->CAMCR);
	अगर (tx_पूर्णांकsup != 0) अणु
		vptr->पूर्णांक_mask &= ~(ISR_PTXI | ISR_PTX0I | ISR_PTX1I |
				ISR_PTX2I | ISR_PTX3I);
		ग_लिखोw(tx_पूर्णांकsup, &regs->ISRCTL);
	पूर्ण अन्यथा
		ग_लिखोw(ISRCTL_TSUPDIS, &regs->ISRCTL);

	/* Set Rx Interrupt Suppression Threshold */
	ग_लिखोb(CAMCR_PS1, &regs->CAMCR);
	अगर (rx_पूर्णांकsup != 0) अणु
		vptr->पूर्णांक_mask &= ~ISR_PRXI;
		ग_लिखोw(rx_पूर्णांकsup, &regs->ISRCTL);
	पूर्ण अन्यथा
		ग_लिखोw(ISRCTL_RSUPDIS, &regs->ISRCTL);

	/* Select page to पूर्णांकerrupt hold समयr */
	ग_लिखोb(0, &regs->CAMCR);
पूर्ण

/**
 *	velocity_init_रेजिस्टरs	-	initialise MAC रेजिस्टरs
 *	@vptr: velocity to init
 *	@type: type of initialisation (hot or cold)
 *
 *	Initialise the MAC on a reset or on first set up on the
 *	hardware.
 */
अटल व्योम velocity_init_रेजिस्टरs(काष्ठा velocity_info *vptr,
				    क्रमागत velocity_init_type type)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	काष्ठा net_device *netdev = vptr->netdev;
	पूर्णांक i, mii_status;

	mac_wol_reset(regs);

	चयन (type) अणु
	हाल VELOCITY_INIT_RESET:
	हाल VELOCITY_INIT_WOL:

		netअगर_stop_queue(netdev);

		/*
		 *	Reset RX to prevent RX poपूर्णांकer not on the 4X location
		 */
		velocity_rx_reset(vptr);
		mac_rx_queue_run(regs);
		mac_rx_queue_wake(regs);

		mii_status = velocity_get_opt_media_mode(vptr);
		अगर (velocity_set_media_mode(vptr, mii_status) != VELOCITY_LINK_CHANGE) अणु
			velocity_prपूर्णांक_link_status(vptr);
			अगर (!(vptr->mii_status & VELOCITY_LINK_FAIL))
				netअगर_wake_queue(netdev);
		पूर्ण

		enable_flow_control_ability(vptr);

		mac_clear_isr(regs);
		ग_लिखोl(CR0_STOP, &regs->CR0Clr);
		ग_लिखोl((CR0_DPOLL | CR0_TXON | CR0_RXON | CR0_STRT),
							&regs->CR0Set);

		अवरोध;

	हाल VELOCITY_INIT_COLD:
	शेष:
		/*
		 *	Do reset
		 */
		velocity_soft_reset(vptr);
		mdelay(5);

		अगर (!vptr->no_eeprom) अणु
			mac_eeprom_reload(regs);
			क्रम (i = 0; i < 6; i++)
				ग_लिखोb(netdev->dev_addr[i], regs->PAR + i);
		पूर्ण

		/*
		 *	clear Pre_ACPI bit.
		 */
		BYTE_REG_BITS_OFF(CFGA_PACPI, &(regs->CFGA));
		mac_set_rx_thresh(regs, vptr->options.rx_thresh);
		mac_set_dma_length(regs, vptr->options.DMA_length);

		ग_लिखोb(WOLCFG_SAM | WOLCFG_SAB, &regs->WOLCFGSet);
		/*
		 *	Back off algorithm use original IEEE standard
		 */
		BYTE_REG_BITS_SET(CFGB_OFSET, (CFGB_CRANDOM | CFGB_CAP | CFGB_MBA | CFGB_BAKOPT), &regs->CFGB);

		/*
		 *	Init CAM filter
		 */
		velocity_init_cam_filter(vptr);

		/*
		 *	Set packet filter: Receive directed and broadcast address
		 */
		velocity_set_multi(netdev);

		/*
		 *	Enable MII स्वतः-polling
		 */
		enable_mii_स्वतःpoll(regs);

		setup_adaptive_पूर्णांकerrupts(vptr);

		ग_लिखोl(vptr->rx.pool_dma, &regs->RDBaseLo);
		ग_लिखोw(vptr->options.numrx - 1, &regs->RDCSize);
		mac_rx_queue_run(regs);
		mac_rx_queue_wake(regs);

		ग_लिखोw(vptr->options.numtx - 1, &regs->TDCSize);

		क्रम (i = 0; i < vptr->tx.numq; i++) अणु
			ग_लिखोl(vptr->tx.pool_dma[i], &regs->TDBaseLo[i]);
			mac_tx_queue_run(regs, i);
		पूर्ण

		init_flow_control_रेजिस्टर(vptr);

		ग_लिखोl(CR0_STOP, &regs->CR0Clr);
		ग_लिखोl((CR0_DPOLL | CR0_TXON | CR0_RXON | CR0_STRT), &regs->CR0Set);

		mii_status = velocity_get_opt_media_mode(vptr);
		netअगर_stop_queue(netdev);

		mii_init(vptr, mii_status);

		अगर (velocity_set_media_mode(vptr, mii_status) != VELOCITY_LINK_CHANGE) अणु
			velocity_prपूर्णांक_link_status(vptr);
			अगर (!(vptr->mii_status & VELOCITY_LINK_FAIL))
				netअगर_wake_queue(netdev);
		पूर्ण

		enable_flow_control_ability(vptr);
		mac_hw_mibs_init(regs);
		mac_ग_लिखो_पूर्णांक_mask(vptr->पूर्णांक_mask, regs);
		mac_clear_isr(regs);

	पूर्ण
पूर्ण

अटल व्योम velocity_give_many_rx_descs(काष्ठा velocity_info *vptr)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	पूर्णांक avail, dirty, unusable;

	/*
	 * RD number must be equal to 4X per hardware spec
	 * (programming guide rev 1.20, p.13)
	 */
	अगर (vptr->rx.filled < 4)
		वापस;

	wmb();

	unusable = vptr->rx.filled & 0x0003;
	dirty = vptr->rx.dirty - unusable;
	क्रम (avail = vptr->rx.filled & 0xfffc; avail; avail--) अणु
		dirty = (dirty > 0) ? dirty - 1 : vptr->options.numrx - 1;
		vptr->rx.ring[dirty].rdesc0.len |= OWNED_BY_NIC;
	पूर्ण

	ग_लिखोw(vptr->rx.filled & 0xfffc, &regs->RBRDU);
	vptr->rx.filled = unusable;
पूर्ण

/**
 *	velocity_init_dma_rings	-	set up DMA rings
 *	@vptr: Velocity to set up
 *
 *	Allocate PCI mapped DMA rings क्रम the receive and transmit layer
 *	to use.
 */
अटल पूर्णांक velocity_init_dma_rings(काष्ठा velocity_info *vptr)
अणु
	काष्ठा velocity_opt *opt = &vptr->options;
	स्थिर अचिन्हित पूर्णांक rx_ring_size = opt->numrx * माप(काष्ठा rx_desc);
	स्थिर अचिन्हित पूर्णांक tx_ring_size = opt->numtx * माप(काष्ठा tx_desc);
	dma_addr_t pool_dma;
	व्योम *pool;
	अचिन्हित पूर्णांक i;

	/*
	 * Allocate all RD/TD rings a single pool.
	 *
	 * dma_alloc_coherent() fulfills the requirement क्रम 64 bytes
	 * alignment
	 */
	pool = dma_alloc_coherent(vptr->dev, tx_ring_size * vptr->tx.numq +
				    rx_ring_size, &pool_dma, GFP_ATOMIC);
	अगर (!pool) अणु
		dev_err(vptr->dev, "%s : DMA memory allocation failed.\n",
			vptr->netdev->name);
		वापस -ENOMEM;
	पूर्ण

	vptr->rx.ring = pool;
	vptr->rx.pool_dma = pool_dma;

	pool += rx_ring_size;
	pool_dma += rx_ring_size;

	क्रम (i = 0; i < vptr->tx.numq; i++) अणु
		vptr->tx.rings[i] = pool;
		vptr->tx.pool_dma[i] = pool_dma;
		pool += tx_ring_size;
		pool_dma += tx_ring_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम velocity_set_rxbufsize(काष्ठा velocity_info *vptr, पूर्णांक mtu)
अणु
	vptr->rx.buf_sz = (mtu <= ETH_DATA_LEN) ? PKT_BUF_SZ : mtu + 32;
पूर्ण

/**
 *	velocity_alloc_rx_buf	-	allocate aligned receive buffer
 *	@vptr: velocity
 *	@idx: ring index
 *
 *	Allocate a new full sized buffer क्रम the reception of a frame and
 *	map it पूर्णांकo PCI space क्रम the hardware to use. The hardware
 *	requires *64* byte alignment of the buffer which makes lअगरe
 *	less fun than would be ideal.
 */
अटल पूर्णांक velocity_alloc_rx_buf(काष्ठा velocity_info *vptr, पूर्णांक idx)
अणु
	काष्ठा rx_desc *rd = &(vptr->rx.ring[idx]);
	काष्ठा velocity_rd_info *rd_info = &(vptr->rx.info[idx]);

	rd_info->skb = netdev_alloc_skb(vptr->netdev, vptr->rx.buf_sz + 64);
	अगर (rd_info->skb == शून्य)
		वापस -ENOMEM;

	/*
	 *	Do the gymnastics to get the buffer head क्रम data at
	 *	64byte alignment.
	 */
	skb_reserve(rd_info->skb,
			64 - ((अचिन्हित दीर्घ) rd_info->skb->data & 63));
	rd_info->skb_dma = dma_map_single(vptr->dev, rd_info->skb->data,
					vptr->rx.buf_sz, DMA_FROM_DEVICE);

	/*
	 *	Fill in the descriptor to match
	 */

	*((u32 *) & (rd->rdesc0)) = 0;
	rd->size = cpu_to_le16(vptr->rx.buf_sz) | RX_INTEN;
	rd->pa_low = cpu_to_le32(rd_info->skb_dma);
	rd->pa_high = 0;
	वापस 0;
पूर्ण


अटल पूर्णांक velocity_rx_refill(काष्ठा velocity_info *vptr)
अणु
	पूर्णांक dirty = vptr->rx.dirty, करोne = 0;

	करो अणु
		काष्ठा rx_desc *rd = vptr->rx.ring + dirty;

		/* Fine क्रम an all zero Rx desc at init समय as well */
		अगर (rd->rdesc0.len & OWNED_BY_NIC)
			अवरोध;

		अगर (!vptr->rx.info[dirty].skb) अणु
			अगर (velocity_alloc_rx_buf(vptr, dirty) < 0)
				अवरोध;
		पूर्ण
		करोne++;
		dirty = (dirty < vptr->options.numrx - 1) ? dirty + 1 : 0;
	पूर्ण जबतक (dirty != vptr->rx.curr);

	अगर (करोne) अणु
		vptr->rx.dirty = dirty;
		vptr->rx.filled += करोne;
	पूर्ण

	वापस करोne;
पूर्ण

/**
 *	velocity_मुक्त_rd_ring	-	मुक्त receive ring
 *	@vptr: velocity to clean up
 *
 *	Free the receive buffers क्रम each ring slot and any
 *	attached socket buffers that need to go away.
 */
अटल व्योम velocity_मुक्त_rd_ring(काष्ठा velocity_info *vptr)
अणु
	पूर्णांक i;

	अगर (vptr->rx.info == शून्य)
		वापस;

	क्रम (i = 0; i < vptr->options.numrx; i++) अणु
		काष्ठा velocity_rd_info *rd_info = &(vptr->rx.info[i]);
		काष्ठा rx_desc *rd = vptr->rx.ring + i;

		स_रखो(rd, 0, माप(*rd));

		अगर (!rd_info->skb)
			जारी;
		dma_unmap_single(vptr->dev, rd_info->skb_dma, vptr->rx.buf_sz,
				 DMA_FROM_DEVICE);
		rd_info->skb_dma = 0;

		dev_kमुक्त_skb(rd_info->skb);
		rd_info->skb = शून्य;
	पूर्ण

	kमुक्त(vptr->rx.info);
	vptr->rx.info = शून्य;
पूर्ण

/**
 *	velocity_init_rd_ring	-	set up receive ring
 *	@vptr: velocity to configure
 *
 *	Allocate and set up the receive buffers क्रम each ring slot and
 *	assign them to the network adapter.
 */
अटल पूर्णांक velocity_init_rd_ring(काष्ठा velocity_info *vptr)
अणु
	पूर्णांक ret = -ENOMEM;

	vptr->rx.info = kसुस्मृति(vptr->options.numrx,
				माप(काष्ठा velocity_rd_info), GFP_KERNEL);
	अगर (!vptr->rx.info)
		जाओ out;

	velocity_init_rx_ring_indexes(vptr);

	अगर (velocity_rx_refill(vptr) != vptr->options.numrx) अणु
		netdev_err(vptr->netdev, "failed to allocate RX buffer\n");
		velocity_मुक्त_rd_ring(vptr);
		जाओ out;
	पूर्ण

	ret = 0;
out:
	वापस ret;
पूर्ण

/**
 *	velocity_init_td_ring	-	set up transmit ring
 *	@vptr:	velocity
 *
 *	Set up the transmit ring and chain the ring poपूर्णांकers together.
 *	Returns zero on success or a negative posix त्रुटि_सं code क्रम
 *	failure.
 */
अटल पूर्णांक velocity_init_td_ring(काष्ठा velocity_info *vptr)
अणु
	पूर्णांक j;

	/* Init the TD ring entries */
	क्रम (j = 0; j < vptr->tx.numq; j++) अणु

		vptr->tx.infos[j] = kसुस्मृति(vptr->options.numtx,
					    माप(काष्ठा velocity_td_info),
					    GFP_KERNEL);
		अगर (!vptr->tx.infos[j])	अणु
			जबतक (--j >= 0)
				kमुक्त(vptr->tx.infos[j]);
			वापस -ENOMEM;
		पूर्ण

		vptr->tx.tail[j] = vptr->tx.curr[j] = vptr->tx.used[j] = 0;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	velocity_मुक्त_dma_rings	-	मुक्त PCI ring poपूर्णांकers
 *	@vptr: Velocity to मुक्त from
 *
 *	Clean up the PCI ring buffers allocated to this velocity.
 */
अटल व्योम velocity_मुक्त_dma_rings(काष्ठा velocity_info *vptr)
अणु
	स्थिर पूर्णांक size = vptr->options.numrx * माप(काष्ठा rx_desc) +
		vptr->options.numtx * माप(काष्ठा tx_desc) * vptr->tx.numq;

	dma_मुक्त_coherent(vptr->dev, size, vptr->rx.ring, vptr->rx.pool_dma);
पूर्ण

अटल पूर्णांक velocity_init_rings(काष्ठा velocity_info *vptr, पूर्णांक mtu)
अणु
	पूर्णांक ret;

	velocity_set_rxbufsize(vptr, mtu);

	ret = velocity_init_dma_rings(vptr);
	अगर (ret < 0)
		जाओ out;

	ret = velocity_init_rd_ring(vptr);
	अगर (ret < 0)
		जाओ err_मुक्त_dma_rings_0;

	ret = velocity_init_td_ring(vptr);
	अगर (ret < 0)
		जाओ err_मुक्त_rd_ring_1;
out:
	वापस ret;

err_मुक्त_rd_ring_1:
	velocity_मुक्त_rd_ring(vptr);
err_मुक्त_dma_rings_0:
	velocity_मुक्त_dma_rings(vptr);
	जाओ out;
पूर्ण

/**
 *	velocity_मुक्त_tx_buf	-	मुक्त transmit buffer
 *	@vptr: velocity
 *	@tdinfo: buffer
 *	@td: transmit descriptor to मुक्त
 *
 *	Release an transmit buffer. If the buffer was pपुनः_स्मृतिated then
 *	recycle it, अगर not then unmap the buffer.
 */
अटल व्योम velocity_मुक्त_tx_buf(काष्ठा velocity_info *vptr,
		काष्ठा velocity_td_info *tdinfo, काष्ठा tx_desc *td)
अणु
	काष्ठा sk_buff *skb = tdinfo->skb;
	पूर्णांक i;

	/*
	 *	Don't unmap the pre-allocated tx_bufs
	 */
	क्रम (i = 0; i < tdinfo->nskb_dma; i++) अणु
		माप_प्रकार pktlen = max_t(माप_प्रकार, skb->len, ETH_ZLEN);

		/* For scatter-gather */
		अगर (skb_shinfo(skb)->nr_frags > 0)
			pktlen = max_t(माप_प्रकार, pktlen,
				       td->td_buf[i].size & ~TD_QUEUE);

		dma_unmap_single(vptr->dev, tdinfo->skb_dma[i],
				 le16_to_cpu(pktlen), DMA_TO_DEVICE);
	पूर्ण
	dev_consume_skb_irq(skb);
	tdinfo->skb = शून्य;
पूर्ण

/*
 *	FIXME: could we merge this with velocity_मुक्त_tx_buf ?
 */
अटल व्योम velocity_मुक्त_td_ring_entry(काष्ठा velocity_info *vptr,
							 पूर्णांक q, पूर्णांक n)
अणु
	काष्ठा velocity_td_info *td_info = &(vptr->tx.infos[q][n]);
	पूर्णांक i;

	अगर (td_info == शून्य)
		वापस;

	अगर (td_info->skb) अणु
		क्रम (i = 0; i < td_info->nskb_dma; i++) अणु
			अगर (td_info->skb_dma[i]) अणु
				dma_unmap_single(vptr->dev, td_info->skb_dma[i],
					td_info->skb->len, DMA_TO_DEVICE);
				td_info->skb_dma[i] = 0;
			पूर्ण
		पूर्ण
		dev_kमुक्त_skb(td_info->skb);
		td_info->skb = शून्य;
	पूर्ण
पूर्ण

/**
 *	velocity_मुक्त_td_ring	-	मुक्त td ring
 *	@vptr: velocity
 *
 *	Free up the transmit ring क्रम this particular velocity adapter.
 *	We मुक्त the ring contents but not the ring itself.
 */
अटल व्योम velocity_मुक्त_td_ring(काष्ठा velocity_info *vptr)
अणु
	पूर्णांक i, j;

	क्रम (j = 0; j < vptr->tx.numq; j++) अणु
		अगर (vptr->tx.infos[j] == शून्य)
			जारी;
		क्रम (i = 0; i < vptr->options.numtx; i++)
			velocity_मुक्त_td_ring_entry(vptr, j, i);

		kमुक्त(vptr->tx.infos[j]);
		vptr->tx.infos[j] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम velocity_मुक्त_rings(काष्ठा velocity_info *vptr)
अणु
	velocity_मुक्त_td_ring(vptr);
	velocity_मुक्त_rd_ring(vptr);
	velocity_मुक्त_dma_rings(vptr);
पूर्ण

/**
 *	velocity_error	-	handle error from controller
 *	@vptr: velocity
 *	@status: card status
 *
 *	Process an error report from the hardware and attempt to recover
 *	the card itself. At the moment we cannot recover from some
 *	theoretically impossible errors but this could be fixed using
 *	the pci_device_failed logic to bounce the hardware
 *
 */
अटल व्योम velocity_error(काष्ठा velocity_info *vptr, पूर्णांक status)
अणु

	अगर (status & ISR_TXSTLI) अणु
		काष्ठा mac_regs __iomem *regs = vptr->mac_regs;

		netdev_err(vptr->netdev, "TD structure error TDindex=%hx\n",
			   पढ़ोw(&regs->TDIdx[0]));
		BYTE_REG_BITS_ON(TXESR_TDSTR, &regs->TXESR);
		ग_लिखोw(TRDCSR_RUN, &regs->TDCSRClr);
		netअगर_stop_queue(vptr->netdev);

		/* FIXME: port over the pci_device_failed code and use it
		   here */
	पूर्ण

	अगर (status & ISR_SRCI) अणु
		काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
		पूर्णांक linked;

		अगर (vptr->options.spd_dpx == SPD_DPX_AUTO) अणु
			vptr->mii_status = check_connection_type(regs);

			/*
			 *	If it is a 3119, disable frame bursting in
			 *	halfduplex mode and enable it in fullduplex
			 *	 mode
			 */
			अगर (vptr->rev_id < REV_ID_VT3216_A0) अणु
				अगर (vptr->mii_status & VELOCITY_DUPLEX_FULL)
					BYTE_REG_BITS_ON(TCR_TB2BDIS, &regs->TCR);
				अन्यथा
					BYTE_REG_BITS_OFF(TCR_TB2BDIS, &regs->TCR);
			पूर्ण
			/*
			 *	Only enable CD heart beat counter in 10HD mode
			 */
			अगर (!(vptr->mii_status & VELOCITY_DUPLEX_FULL) && (vptr->mii_status & VELOCITY_SPEED_10))
				BYTE_REG_BITS_OFF(TESTCFG_HBDIS, &regs->TESTCFG);
			अन्यथा
				BYTE_REG_BITS_ON(TESTCFG_HBDIS, &regs->TESTCFG);

			setup_queue_समयrs(vptr);
		पूर्ण
		/*
		 *	Get link status from PHYSR0
		 */
		linked = पढ़ोb(&regs->PHYSR0) & PHYSR0_LINKGD;

		अगर (linked) अणु
			vptr->mii_status &= ~VELOCITY_LINK_FAIL;
			netअगर_carrier_on(vptr->netdev);
		पूर्ण अन्यथा अणु
			vptr->mii_status |= VELOCITY_LINK_FAIL;
			netअगर_carrier_off(vptr->netdev);
		पूर्ण

		velocity_prपूर्णांक_link_status(vptr);
		enable_flow_control_ability(vptr);

		/*
		 *	Re-enable स्वतः-polling because SRCI will disable
		 *	स्वतः-polling
		 */

		enable_mii_स्वतःpoll(regs);

		अगर (vptr->mii_status & VELOCITY_LINK_FAIL)
			netअगर_stop_queue(vptr->netdev);
		अन्यथा
			netअगर_wake_queue(vptr->netdev);

	पूर्ण
	अगर (status & ISR_MIBFI)
		velocity_update_hw_mibs(vptr);
	अगर (status & ISR_LSTEI)
		mac_rx_queue_wake(vptr->mac_regs);
पूर्ण

/**
 *	tx_srv		-	transmit पूर्णांकerrupt service
 *	@vptr: Velocity
 *
 *	Scan the queues looking क्रम transmitted packets that
 *	we can complete and clean up. Update any statistics as
 *	necessary/
 */
अटल पूर्णांक velocity_tx_srv(काष्ठा velocity_info *vptr)
अणु
	काष्ठा tx_desc *td;
	पूर्णांक qnum;
	पूर्णांक full = 0;
	पूर्णांक idx;
	पूर्णांक works = 0;
	काष्ठा velocity_td_info *tdinfo;
	काष्ठा net_device_stats *stats = &vptr->netdev->stats;

	क्रम (qnum = 0; qnum < vptr->tx.numq; qnum++) अणु
		क्रम (idx = vptr->tx.tail[qnum]; vptr->tx.used[qnum] > 0;
			idx = (idx + 1) % vptr->options.numtx) अणु

			/*
			 *	Get Tx Descriptor
			 */
			td = &(vptr->tx.rings[qnum][idx]);
			tdinfo = &(vptr->tx.infos[qnum][idx]);

			अगर (td->tdesc0.len & OWNED_BY_NIC)
				अवरोध;

			अगर ((works++ > 15))
				अवरोध;

			अगर (td->tdesc0.TSR & TSR0_TERR) अणु
				stats->tx_errors++;
				stats->tx_dropped++;
				अगर (td->tdesc0.TSR & TSR0_CDH)
					stats->tx_heartbeat_errors++;
				अगर (td->tdesc0.TSR & TSR0_CRS)
					stats->tx_carrier_errors++;
				अगर (td->tdesc0.TSR & TSR0_ABT)
					stats->tx_पातed_errors++;
				अगर (td->tdesc0.TSR & TSR0_OWC)
					stats->tx_winकरोw_errors++;
			पूर्ण अन्यथा अणु
				stats->tx_packets++;
				stats->tx_bytes += tdinfo->skb->len;
			पूर्ण
			velocity_मुक्त_tx_buf(vptr, tdinfo, td);
			vptr->tx.used[qnum]--;
		पूर्ण
		vptr->tx.tail[qnum] = idx;

		अगर (AVAIL_TD(vptr, qnum) < 1)
			full = 1;
	पूर्ण
	/*
	 *	Look to see अगर we should kick the transmit network
	 *	layer क्रम more work.
	 */
	अगर (netअगर_queue_stopped(vptr->netdev) && (full == 0) &&
	    (!(vptr->mii_status & VELOCITY_LINK_FAIL))) अणु
		netअगर_wake_queue(vptr->netdev);
	पूर्ण
	वापस works;
पूर्ण

/**
 *	velocity_rx_csum	-	checksum process
 *	@rd: receive packet descriptor
 *	@skb: network layer packet buffer
 *
 *	Process the status bits क्रम the received packet and determine
 *	अगर the checksum was computed and verअगरied by the hardware
 */
अटल अंतरभूत व्योम velocity_rx_csum(काष्ठा rx_desc *rd, काष्ठा sk_buff *skb)
अणु
	skb_checksum_none_निश्चित(skb);

	अगर (rd->rdesc1.CSM & CSM_IPKT) अणु
		अगर (rd->rdesc1.CSM & CSM_IPOK) अणु
			अगर ((rd->rdesc1.CSM & CSM_TCPKT) ||
					(rd->rdesc1.CSM & CSM_UDPKT)) अणु
				अगर (!(rd->rdesc1.CSM & CSM_TUPOK))
					वापस;
			पूर्ण
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	velocity_rx_copy	-	in place Rx copy क्रम small packets
 *	@rx_skb: network layer packet buffer candidate
 *	@pkt_size: received data size
 *	@vptr: velocity adapter
 *
 *	Replace the current skb that is scheduled क्रम Rx processing by a
 *	लघुer, immediately allocated skb, अगर the received packet is small
 *	enough. This function वापसs a negative value अगर the received
 *	packet is too big or अगर memory is exhausted.
 */
अटल पूर्णांक velocity_rx_copy(काष्ठा sk_buff **rx_skb, पूर्णांक pkt_size,
			    काष्ठा velocity_info *vptr)
अणु
	पूर्णांक ret = -1;
	अगर (pkt_size < rx_copyअवरोध) अणु
		काष्ठा sk_buff *new_skb;

		new_skb = netdev_alloc_skb_ip_align(vptr->netdev, pkt_size);
		अगर (new_skb) अणु
			new_skb->ip_summed = rx_skb[0]->ip_summed;
			skb_copy_from_linear_data(*rx_skb, new_skb->data, pkt_size);
			*rx_skb = new_skb;
			ret = 0;
		पूर्ण

	पूर्ण
	वापस ret;
पूर्ण

/**
 *	velocity_iph_realign	-	IP header alignment
 *	@vptr: velocity we are handling
 *	@skb: network layer packet buffer
 *	@pkt_size: received data size
 *
 *	Align IP header on a 2 bytes boundary. This behavior can be
 *	configured by the user.
 */
अटल अंतरभूत व्योम velocity_iph_realign(काष्ठा velocity_info *vptr,
					काष्ठा sk_buff *skb, पूर्णांक pkt_size)
अणु
	अगर (vptr->flags & VELOCITY_FLAGS_IP_ALIGN) अणु
		स_हटाओ(skb->data + 2, skb->data, pkt_size);
		skb_reserve(skb, 2);
	पूर्ण
पूर्ण

/**
 *	velocity_receive_frame	-	received packet processor
 *	@vptr: velocity we are handling
 *	@idx: ring index
 *
 *	A packet has arrived. We process the packet and अगर appropriate
 *	pass the frame up the network stack
 */
अटल पूर्णांक velocity_receive_frame(काष्ठा velocity_info *vptr, पूर्णांक idx)
अणु
	काष्ठा net_device_stats *stats = &vptr->netdev->stats;
	काष्ठा velocity_rd_info *rd_info = &(vptr->rx.info[idx]);
	काष्ठा rx_desc *rd = &(vptr->rx.ring[idx]);
	पूर्णांक pkt_len = le16_to_cpu(rd->rdesc0.len) & 0x3fff;
	काष्ठा sk_buff *skb;

	अगर (unlikely(rd->rdesc0.RSR & (RSR_STP | RSR_EDP | RSR_RL))) अणु
		अगर (rd->rdesc0.RSR & (RSR_STP | RSR_EDP))
			netdev_err(vptr->netdev, "received frame spans multiple RDs\n");
		stats->rx_length_errors++;
		वापस -EINVAL;
	पूर्ण

	अगर (rd->rdesc0.RSR & RSR_MAR)
		stats->multicast++;

	skb = rd_info->skb;

	dma_sync_single_क्रम_cpu(vptr->dev, rd_info->skb_dma,
				    vptr->rx.buf_sz, DMA_FROM_DEVICE);

	velocity_rx_csum(rd, skb);

	अगर (velocity_rx_copy(&skb, pkt_len, vptr) < 0) अणु
		velocity_iph_realign(vptr, skb, pkt_len);
		rd_info->skb = शून्य;
		dma_unmap_single(vptr->dev, rd_info->skb_dma, vptr->rx.buf_sz,
				 DMA_FROM_DEVICE);
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_device(vptr->dev, rd_info->skb_dma,
					   vptr->rx.buf_sz, DMA_FROM_DEVICE);
	पूर्ण

	skb_put(skb, pkt_len - 4);
	skb->protocol = eth_type_trans(skb, vptr->netdev);

	अगर (rd->rdesc0.RSR & RSR_DETAG) अणु
		u16 vid = swab16(le16_to_cpu(rd->rdesc1.PQTAG));

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	पूर्ण
	netअगर_receive_skb(skb);

	stats->rx_bytes += pkt_len;
	stats->rx_packets++;

	वापस 0;
पूर्ण

/**
 *	velocity_rx_srv		-	service RX पूर्णांकerrupt
 *	@vptr: velocity
 *	@budget_left: reमुख्यing budget
 *
 *	Walk the receive ring of the velocity adapter and हटाओ
 *	any received packets from the receive queue. Hand the ring
 *	slots back to the adapter क्रम reuse.
 */
अटल पूर्णांक velocity_rx_srv(काष्ठा velocity_info *vptr, पूर्णांक budget_left)
अणु
	काष्ठा net_device_stats *stats = &vptr->netdev->stats;
	पूर्णांक rd_curr = vptr->rx.curr;
	पूर्णांक works = 0;

	जबतक (works < budget_left) अणु
		काष्ठा rx_desc *rd = vptr->rx.ring + rd_curr;

		अगर (!vptr->rx.info[rd_curr].skb)
			अवरोध;

		अगर (rd->rdesc0.len & OWNED_BY_NIC)
			अवरोध;

		rmb();

		/*
		 *	Don't drop CE or RL error frame although RXOK is off
		 */
		अगर (rd->rdesc0.RSR & (RSR_RXOK | RSR_CE | RSR_RL)) अणु
			अगर (velocity_receive_frame(vptr, rd_curr) < 0)
				stats->rx_dropped++;
		पूर्ण अन्यथा अणु
			अगर (rd->rdesc0.RSR & RSR_CRC)
				stats->rx_crc_errors++;
			अगर (rd->rdesc0.RSR & RSR_FAE)
				stats->rx_frame_errors++;

			stats->rx_dropped++;
		पूर्ण

		rd->size |= RX_INTEN;

		rd_curr++;
		अगर (rd_curr >= vptr->options.numrx)
			rd_curr = 0;
		works++;
	पूर्ण

	vptr->rx.curr = rd_curr;

	अगर ((works > 0) && (velocity_rx_refill(vptr) > 0))
		velocity_give_many_rx_descs(vptr);

	VAR_USED(stats);
	वापस works;
पूर्ण

अटल पूर्णांक velocity_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा velocity_info *vptr = container_of(napi,
			काष्ठा velocity_info, napi);
	अचिन्हित पूर्णांक rx_करोne;
	अचिन्हित दीर्घ flags;

	/*
	 * Do rx and tx twice क्रम perक्रमmance (taken from the VIA
	 * out-of-tree driver).
	 */
	rx_करोne = velocity_rx_srv(vptr, budget);
	spin_lock_irqsave(&vptr->lock, flags);
	velocity_tx_srv(vptr);
	/* If budget not fully consumed, निकास the polling mode */
	अगर (rx_करोne < budget) अणु
		napi_complete_करोne(napi, rx_करोne);
		mac_enable_पूर्णांक(vptr->mac_regs);
	पूर्ण
	spin_unlock_irqrestore(&vptr->lock, flags);

	वापस rx_करोne;
पूर्ण

/**
 *	velocity_पूर्णांकr		-	पूर्णांकerrupt callback
 *	@irq: पूर्णांकerrupt number
 *	@dev_instance: पूर्णांकerrupting device
 *
 *	Called whenever an पूर्णांकerrupt is generated by the velocity
 *	adapter IRQ line. We may not be the source of the पूर्णांकerrupt
 *	and need to identअगरy initially अगर we are, and अगर not निकास as
 *	efficiently as possible.
 */
अटल irqवापस_t velocity_पूर्णांकr(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	u32 isr_status;

	spin_lock(&vptr->lock);
	isr_status = mac_पढ़ो_isr(vptr->mac_regs);

	/* Not us ? */
	अगर (isr_status == 0) अणु
		spin_unlock(&vptr->lock);
		वापस IRQ_NONE;
	पूर्ण

	/* Ack the पूर्णांकerrupt */
	mac_ग_लिखो_isr(vptr->mac_regs, isr_status);

	अगर (likely(napi_schedule_prep(&vptr->napi))) अणु
		mac_disable_पूर्णांक(vptr->mac_regs);
		__napi_schedule(&vptr->napi);
	पूर्ण

	अगर (isr_status & (~(ISR_PRXI | ISR_PPRXI | ISR_PTXI | ISR_PPTXI)))
		velocity_error(vptr, isr_status);

	spin_unlock(&vptr->lock);

	वापस IRQ_HANDLED;
पूर्ण

/**
 *	velocity_खोलो		-	पूर्णांकerface activation callback
 *	@dev: network layer device to खोलो
 *
 *	Called when the network layer brings the पूर्णांकerface up. Returns
 *	a negative posix error code on failure, or zero on success.
 *
 *	All the ring allocation and set up is करोne on खोलो क्रम this
 *	adapter to minimise memory usage when inactive
 */
अटल पूर्णांक velocity_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	पूर्णांक ret;

	ret = velocity_init_rings(vptr, dev->mtu);
	अगर (ret < 0)
		जाओ out;

	/* Ensure chip is running */
	velocity_set_घातer_state(vptr, PCI_D0);

	velocity_init_रेजिस्टरs(vptr, VELOCITY_INIT_COLD);

	ret = request_irq(dev->irq, velocity_पूर्णांकr, IRQF_SHARED,
			  dev->name, dev);
	अगर (ret < 0) अणु
		/* Power करोwn the chip */
		velocity_set_घातer_state(vptr, PCI_D3hot);
		velocity_मुक्त_rings(vptr);
		जाओ out;
	पूर्ण

	velocity_give_many_rx_descs(vptr);

	mac_enable_पूर्णांक(vptr->mac_regs);
	netअगर_start_queue(dev);
	napi_enable(&vptr->napi);
	vptr->flags |= VELOCITY_FLAGS_OPENED;
out:
	वापस ret;
पूर्ण

/**
 *	velocity_shutकरोwn	-	shut करोwn the chip
 *	@vptr: velocity to deactivate
 *
 *	Shuts करोwn the पूर्णांकernal operations of the velocity and
 *	disables पूर्णांकerrupts, स्वतःpolling, transmit and receive
 */
अटल व्योम velocity_shutकरोwn(काष्ठा velocity_info *vptr)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	mac_disable_पूर्णांक(regs);
	ग_लिखोl(CR0_STOP, &regs->CR0Set);
	ग_लिखोw(0xFFFF, &regs->TDCSRClr);
	ग_लिखोb(0xFF, &regs->RDCSRClr);
	safe_disable_mii_स्वतःpoll(regs);
	mac_clear_isr(regs);
पूर्ण

/**
 *	velocity_change_mtu	-	MTU change callback
 *	@dev: network device
 *	@new_mtu: desired MTU
 *
 *	Handle requests from the networking layer क्रम MTU change on
 *	this पूर्णांकerface. It माला_लो called on a change by the network layer.
 *	Return zero क्रम success or negative posix error code.
 */
अटल पूर्णांक velocity_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (!netअगर_running(dev)) अणु
		dev->mtu = new_mtu;
		जाओ out_0;
	पूर्ण

	अगर (dev->mtu != new_mtu) अणु
		काष्ठा velocity_info *पंचांगp_vptr;
		अचिन्हित दीर्घ flags;
		काष्ठा rx_info rx;
		काष्ठा tx_info tx;

		पंचांगp_vptr = kzalloc(माप(*पंचांगp_vptr), GFP_KERNEL);
		अगर (!पंचांगp_vptr) अणु
			ret = -ENOMEM;
			जाओ out_0;
		पूर्ण

		पंचांगp_vptr->netdev = dev;
		पंचांगp_vptr->pdev = vptr->pdev;
		पंचांगp_vptr->dev = vptr->dev;
		पंचांगp_vptr->options = vptr->options;
		पंचांगp_vptr->tx.numq = vptr->tx.numq;

		ret = velocity_init_rings(पंचांगp_vptr, new_mtu);
		अगर (ret < 0)
			जाओ out_मुक्त_पंचांगp_vptr_1;

		napi_disable(&vptr->napi);

		spin_lock_irqsave(&vptr->lock, flags);

		netअगर_stop_queue(dev);
		velocity_shutकरोwn(vptr);

		rx = vptr->rx;
		tx = vptr->tx;

		vptr->rx = पंचांगp_vptr->rx;
		vptr->tx = पंचांगp_vptr->tx;

		पंचांगp_vptr->rx = rx;
		पंचांगp_vptr->tx = tx;

		dev->mtu = new_mtu;

		velocity_init_रेजिस्टरs(vptr, VELOCITY_INIT_COLD);

		velocity_give_many_rx_descs(vptr);

		napi_enable(&vptr->napi);

		mac_enable_पूर्णांक(vptr->mac_regs);
		netअगर_start_queue(dev);

		spin_unlock_irqrestore(&vptr->lock, flags);

		velocity_मुक्त_rings(पंचांगp_vptr);

out_मुक्त_पंचांगp_vptr_1:
		kमुक्त(पंचांगp_vptr);
	पूर्ण
out_0:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 *  velocity_poll_controller		-	Velocity Poll controller function
 *  @dev: network device
 *
 *
 *  Used by NETCONSOLE and other diagnostic tools to allow network I/P
 *  with पूर्णांकerrupts disabled.
 */
अटल व्योम velocity_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	velocity_पूर्णांकr(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/**
 *	velocity_mii_ioctl		-	MII ioctl handler
 *	@dev: network device
 *	@अगरr: the अगरreq block क्रम the ioctl
 *	@cmd: the command
 *
 *	Process MII requests made via ioctl from the network layer. These
 *	are used by tools like kudzu to पूर्णांकerrogate the link state of the
 *	hardware
 */
अटल पूर्णांक velocity_mii_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	अचिन्हित दीर्घ flags;
	काष्ठा mii_ioctl_data *miidata = अगर_mii(अगरr);
	पूर्णांक err;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		miidata->phy_id = पढ़ोb(&regs->MIIADR) & 0x1f;
		अवरोध;
	हाल SIOCGMIIREG:
		अगर (velocity_mii_पढ़ो(vptr->mac_regs, miidata->reg_num & 0x1f, &(miidata->val_out)) < 0)
			वापस -ETIMEDOUT;
		अवरोध;
	हाल SIOCSMIIREG:
		spin_lock_irqsave(&vptr->lock, flags);
		err = velocity_mii_ग_लिखो(vptr->mac_regs, miidata->reg_num & 0x1f, miidata->val_in);
		spin_unlock_irqrestore(&vptr->lock, flags);
		check_connection_type(vptr->mac_regs);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	velocity_ioctl		-	ioctl entry poपूर्णांक
 *	@dev: network device
 *	@rq: पूर्णांकerface request ioctl
 *	@cmd: command code
 *
 *	Called when the user issues an ioctl request to the network
 *	device in question. The velocity पूर्णांकerface supports MII.
 */
अटल पूर्णांक velocity_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	पूर्णांक ret;

	/* If we are asked क्रम inक्रमmation and the device is घातer
	   saving then we need to bring the device back up to talk to it */

	अगर (!netअगर_running(dev))
		velocity_set_घातer_state(vptr, PCI_D0);

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:	/* Get address of MII PHY in use. */
	हाल SIOCGMIIREG:	/* Read MII PHY रेजिस्टर. */
	हाल SIOCSMIIREG:	/* Write to MII PHY रेजिस्टर. */
		ret = velocity_mii_ioctl(dev, rq, cmd);
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण
	अगर (!netअगर_running(dev))
		velocity_set_घातer_state(vptr, PCI_D3hot);


	वापस ret;
पूर्ण

/**
 *	velocity_get_status	-	statistics callback
 *	@dev: network device
 *
 *	Callback from the network layer to allow driver statistics
 *	to be resynchronized with hardware collected state. In the
 *	हाल of the velocity we need to pull the MIB counters from
 *	the hardware पूर्णांकo the counters beक्रमe letting the network
 *	layer display them.
 */
अटल काष्ठा net_device_stats *velocity_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	/* If the hardware is करोwn, करोn't touch MII */
	अगर (!netअगर_running(dev))
		वापस &dev->stats;

	spin_lock_irq(&vptr->lock);
	velocity_update_hw_mibs(vptr);
	spin_unlock_irq(&vptr->lock);

	dev->stats.rx_packets = vptr->mib_counter[HW_MIB_अगरRxAllPkts];
	dev->stats.rx_errors = vptr->mib_counter[HW_MIB_अगरRxErrorPkts];
	dev->stats.rx_length_errors = vptr->mib_counter[HW_MIB_अगरInRangeLengthErrors];

//  अचिन्हित दीर्घ   rx_dropped;     /* no space in linux buffers    */
	dev->stats.collisions = vptr->mib_counter[HW_MIB_अगरTxEtherCollisions];
	/* detailed rx_errors: */
//  अचिन्हित दीर्घ   rx_length_errors;
//  अचिन्हित दीर्घ   rx_over_errors;     /* receiver ring buff overflow  */
	dev->stats.rx_crc_errors = vptr->mib_counter[HW_MIB_अगरRxPktCRCE];
//  अचिन्हित दीर्घ   rx_frame_errors;    /* recv'd frame alignment error */
//  अचिन्हित दीर्घ   rx_fअगरo_errors;     /* recv'r fअगरo overrun      */
//  अचिन्हित दीर्घ   rx_missed_errors;   /* receiver missed packet   */

	/* detailed tx_errors */
//  अचिन्हित दीर्घ   tx_fअगरo_errors;

	वापस &dev->stats;
पूर्ण

/**
 *	velocity_बंद		-	बंद adapter callback
 *	@dev: network device
 *
 *	Callback from the network layer when the velocity is being
 *	deactivated by the network layer
 */
अटल पूर्णांक velocity_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	napi_disable(&vptr->napi);
	netअगर_stop_queue(dev);
	velocity_shutकरोwn(vptr);

	अगर (vptr->flags & VELOCITY_FLAGS_WOL_ENABLED)
		velocity_get_ip(vptr);

	मुक्त_irq(dev->irq, dev);

	velocity_मुक्त_rings(vptr);

	vptr->flags &= (~VELOCITY_FLAGS_OPENED);
	वापस 0;
पूर्ण

/**
 *	velocity_xmit		-	transmit packet callback
 *	@skb: buffer to transmit
 *	@dev: network device
 *
 *	Called by the network layer to request a packet is queued to
 *	the velocity. Returns zero on success.
 */
अटल netdev_tx_t velocity_xmit(काष्ठा sk_buff *skb,
				 काष्ठा net_device *dev)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	पूर्णांक qnum = 0;
	काष्ठा tx_desc *td_ptr;
	काष्ठा velocity_td_info *tdinfo;
	अचिन्हित दीर्घ flags;
	पूर्णांक pktlen;
	पूर्णांक index, prev;
	पूर्णांक i = 0;

	अगर (skb_padto(skb, ETH_ZLEN))
		जाओ out;

	/* The hardware can handle at most 7 memory segments, so merge
	 * the skb अगर there are more */
	अगर (skb_shinfo(skb)->nr_frags > 6 && __skb_linearize(skb)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	pktlen = skb_shinfo(skb)->nr_frags == 0 ?
			max_t(अचिन्हित पूर्णांक, skb->len, ETH_ZLEN) :
				skb_headlen(skb);

	spin_lock_irqsave(&vptr->lock, flags);

	index = vptr->tx.curr[qnum];
	td_ptr = &(vptr->tx.rings[qnum][index]);
	tdinfo = &(vptr->tx.infos[qnum][index]);

	td_ptr->tdesc1.TCR = TCR0_TIC;
	td_ptr->td_buf[0].size &= ~TD_QUEUE;

	/*
	 *	Map the linear network buffer पूर्णांकo PCI space and
	 *	add it to the transmit ring.
	 */
	tdinfo->skb = skb;
	tdinfo->skb_dma[0] = dma_map_single(vptr->dev, skb->data, pktlen,
								DMA_TO_DEVICE);
	td_ptr->tdesc0.len = cpu_to_le16(pktlen);
	td_ptr->td_buf[0].pa_low = cpu_to_le32(tdinfo->skb_dma[0]);
	td_ptr->td_buf[0].pa_high = 0;
	td_ptr->td_buf[0].size = cpu_to_le16(pktlen);

	/* Handle fragments */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		tdinfo->skb_dma[i + 1] = skb_frag_dma_map(vptr->dev,
							  frag, 0,
							  skb_frag_size(frag),
							  DMA_TO_DEVICE);

		td_ptr->td_buf[i + 1].pa_low = cpu_to_le32(tdinfo->skb_dma[i + 1]);
		td_ptr->td_buf[i + 1].pa_high = 0;
		td_ptr->td_buf[i + 1].size = cpu_to_le16(skb_frag_size(frag));
	पूर्ण
	tdinfo->nskb_dma = i + 1;

	td_ptr->tdesc1.cmd = TCPLS_NORMAL + (tdinfo->nskb_dma + 1) * 16;

	अगर (skb_vlan_tag_present(skb)) अणु
		td_ptr->tdesc1.vlan = cpu_to_le16(skb_vlan_tag_get(skb));
		td_ptr->tdesc1.TCR |= TCR0_VETAG;
	पूर्ण

	/*
	 *	Handle hardware checksum
	 */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		स्थिर काष्ठा iphdr *ip = ip_hdr(skb);
		अगर (ip->protocol == IPPROTO_TCP)
			td_ptr->tdesc1.TCR |= TCR0_TCPCK;
		अन्यथा अगर (ip->protocol == IPPROTO_UDP)
			td_ptr->tdesc1.TCR |= (TCR0_UDPCK);
		td_ptr->tdesc1.TCR |= TCR0_IPCK;
	पूर्ण

	prev = index - 1;
	अगर (prev < 0)
		prev = vptr->options.numtx - 1;
	td_ptr->tdesc0.len |= OWNED_BY_NIC;
	vptr->tx.used[qnum]++;
	vptr->tx.curr[qnum] = (index + 1) % vptr->options.numtx;

	अगर (AVAIL_TD(vptr, qnum) < 1)
		netअगर_stop_queue(dev);

	td_ptr = &(vptr->tx.rings[qnum][prev]);
	td_ptr->td_buf[0].size |= TD_QUEUE;
	mac_tx_queue_wake(vptr->mac_regs, qnum);

	spin_unlock_irqrestore(&vptr->lock, flags);
out:
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops velocity_netdev_ops = अणु
	.nकरो_खोलो		= velocity_खोलो,
	.nकरो_stop		= velocity_बंद,
	.nकरो_start_xmit		= velocity_xmit,
	.nकरो_get_stats		= velocity_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_set_rx_mode	= velocity_set_multi,
	.nकरो_change_mtu		= velocity_change_mtu,
	.nकरो_करो_ioctl		= velocity_ioctl,
	.nकरो_vlan_rx_add_vid	= velocity_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= velocity_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = velocity_poll_controller,
#पूर्ण_अगर
पूर्ण;

/**
 *	velocity_init_info	-	init निजी data
 *	@vptr: Velocity info
 *	@info: Board type
 *
 *	Set up the initial velocity_info काष्ठा क्रम the device that has been
 *	discovered.
 */
अटल व्योम velocity_init_info(काष्ठा velocity_info *vptr,
				स्थिर काष्ठा velocity_info_tbl *info)
अणु
	vptr->chip_id = info->chip_id;
	vptr->tx.numq = info->txqueue;
	vptr->multicast_limit = MCAM_SIZE;
	spin_lock_init(&vptr->lock);
पूर्ण

/**
 *	velocity_get_pci_info	-	retrieve PCI info क्रम device
 *	@vptr: velocity device
 *
 *	Retrieve the PCI configuration space data that पूर्णांकerests us from
 *	the kernel PCI layer
 */
अटल पूर्णांक velocity_get_pci_info(काष्ठा velocity_info *vptr)
अणु
	काष्ठा pci_dev *pdev = vptr->pdev;

	pci_set_master(pdev);

	vptr->ioaddr = pci_resource_start(pdev, 0);
	vptr->memaddr = pci_resource_start(pdev, 1);

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_IO)) अणु
		dev_err(&pdev->dev,
			   "region #0 is not an I/O resource, aborting.\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((pci_resource_flags(pdev, 1) & IORESOURCE_IO)) अणु
		dev_err(&pdev->dev,
			   "region #1 is an I/O resource, aborting.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pci_resource_len(pdev, 1) < VELOCITY_IO_SIZE) अणु
		dev_err(&pdev->dev, "region #1 is too small.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	velocity_get_platक्रमm_info - retrieve platक्रमm info क्रम device
 *	@vptr: velocity device
 *
 *	Retrieve the Platक्रमm configuration data that पूर्णांकerests us
 */
अटल पूर्णांक velocity_get_platक्रमm_info(काष्ठा velocity_info *vptr)
अणु
	काष्ठा resource res;
	पूर्णांक ret;

	अगर (of_get_property(vptr->dev->of_node, "no-eeprom", शून्य))
		vptr->no_eeprom = 1;

	ret = of_address_to_resource(vptr->dev->of_node, 0, &res);
	अगर (ret) अणु
		dev_err(vptr->dev, "unable to find memory address\n");
		वापस ret;
	पूर्ण

	vptr->memaddr = res.start;

	अगर (resource_size(&res) < VELOCITY_IO_SIZE) अणु
		dev_err(vptr->dev, "memory region is too small.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	velocity_prपूर्णांक_info	-	per driver data
 *	@vptr: velocity
 *
 *	Prपूर्णांक per driver data as the kernel driver finds Velocity
 *	hardware
 */
अटल व्योम velocity_prपूर्णांक_info(काष्ठा velocity_info *vptr)
अणु
	netdev_info(vptr->netdev, "%s - Ethernet Address: %pM\n",
		    get_chip_name(vptr->chip_id), vptr->netdev->dev_addr);
पूर्ण

अटल u32 velocity_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	वापस BYTE_REG_BITS_IS_ON(PHYSR0_LINKGD, &regs->PHYSR0) ? 1 : 0;
पूर्ण

/**
 *	velocity_probe - set up discovered velocity device
 *	@dev: PCI device
 *	@info: table of match
 *	@irq: पूर्णांकerrupt info
 *	@bustype: bus that device is connected to
 *
 *	Configure a discovered adapter from scratch. Return a negative
 *	त्रुटि_सं error code on failure paths.
 */
अटल पूर्णांक velocity_probe(काष्ठा device *dev, पूर्णांक irq,
			   स्थिर काष्ठा velocity_info_tbl *info,
			   क्रमागत velocity_bus_type bustype)
अणु
	काष्ठा net_device *netdev;
	पूर्णांक i;
	काष्ठा velocity_info *vptr;
	काष्ठा mac_regs __iomem *regs;
	पूर्णांक ret = -ENOMEM;

	/* FIXME: this driver, like almost all other ethernet drivers,
	 * can support more than MAX_UNITS.
	 */
	अगर (velocity_nics >= MAX_UNITS) अणु
		dev_notice(dev, "already found %d NICs.\n", velocity_nics);
		वापस -ENODEV;
	पूर्ण

	netdev = alloc_etherdev(माप(काष्ठा velocity_info));
	अगर (!netdev)
		जाओ out;

	/* Chain it all together */

	SET_NETDEV_DEV(netdev, dev);
	vptr = netdev_priv(netdev);

	pr_info_once("%s Ver. %s\n", VELOCITY_FULL_DRV_NAM, VELOCITY_VERSION);
	pr_info_once("Copyright (c) 2002, 2003 VIA Networking Technologies, Inc.\n");
	pr_info_once("Copyright (c) 2004 Red Hat Inc.\n");

	netdev->irq = irq;
	vptr->netdev = netdev;
	vptr->dev = dev;

	velocity_init_info(vptr, info);

	अगर (bustype == BUS_PCI) अणु
		vptr->pdev = to_pci_dev(dev);

		ret = velocity_get_pci_info(vptr);
		अगर (ret < 0)
			जाओ err_मुक्त_dev;
	पूर्ण अन्यथा अणु
		vptr->pdev = शून्य;
		ret = velocity_get_platक्रमm_info(vptr);
		अगर (ret < 0)
			जाओ err_मुक्त_dev;
	पूर्ण

	regs = ioremap(vptr->memaddr, VELOCITY_IO_SIZE);
	अगर (regs == शून्य) अणु
		ret = -EIO;
		जाओ err_मुक्त_dev;
	पूर्ण

	vptr->mac_regs = regs;
	vptr->rev_id = पढ़ोb(&regs->rev_id);

	mac_wol_reset(regs);

	क्रम (i = 0; i < 6; i++)
		netdev->dev_addr[i] = पढ़ोb(&regs->PAR[i]);


	velocity_get_options(&vptr->options, velocity_nics);

	/*
	 *	Mask out the options cannot be set to the chip
	 */

	vptr->options.flags &= info->flags;

	/*
	 *	Enable the chip specअगरied capbilities
	 */

	vptr->flags = vptr->options.flags | (info->flags & 0xFF000000UL);

	vptr->wol_opts = vptr->options.wol_opts;
	vptr->flags |= VELOCITY_FLAGS_WOL_ENABLED;

	vptr->phy_id = MII_GET_PHY_ID(vptr->mac_regs);

	netdev->netdev_ops = &velocity_netdev_ops;
	netdev->ethtool_ops = &velocity_ethtool_ops;
	netअगर_napi_add(netdev, &vptr->napi, velocity_poll,
							VELOCITY_NAPI_WEIGHT);

	netdev->hw_features = NETIF_F_IP_CSUM | NETIF_F_SG |
			   NETIF_F_HW_VLAN_CTAG_TX;
	netdev->features |= NETIF_F_HW_VLAN_CTAG_TX |
			NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_VLAN_CTAG_RX |
			NETIF_F_IP_CSUM;

	/* MTU range: 64 - 9000 */
	netdev->min_mtu = VELOCITY_MIN_MTU;
	netdev->max_mtu = VELOCITY_MAX_MTU;

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret < 0)
		जाओ err_iounmap;

	अगर (!velocity_get_link(netdev)) अणु
		netअगर_carrier_off(netdev);
		vptr->mii_status |= VELOCITY_LINK_FAIL;
	पूर्ण

	velocity_prपूर्णांक_info(vptr);
	dev_set_drvdata(vptr->dev, netdev);

	/* and leave the chip घातered करोwn */

	velocity_set_घातer_state(vptr, PCI_D3hot);
	velocity_nics++;
out:
	वापस ret;

err_iounmap:
	netअगर_napi_del(&vptr->napi);
	iounmap(regs);
err_मुक्त_dev:
	मुक्त_netdev(netdev);
	जाओ out;
पूर्ण

/**
 *	velocity_हटाओ	- device unplug
 *	@dev: device being हटाओd
 *
 *	Device unload callback. Called on an unplug or on module
 *	unload क्रम each active device that is present. Disconnects
 *	the device from the network layer and मुक्तs all the resources
 */
अटल पूर्णांक velocity_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा velocity_info *vptr = netdev_priv(netdev);

	unरेजिस्टर_netdev(netdev);
	netअगर_napi_del(&vptr->napi);
	iounmap(vptr->mac_regs);
	मुक्त_netdev(netdev);
	velocity_nics--;

	वापस 0;
पूर्ण

अटल पूर्णांक velocity_pci_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा velocity_info_tbl *info =
					&chip_info_table[ent->driver_data];
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret < 0)
		वापस ret;

	ret = pci_request_regions(pdev, VELOCITY_NAME);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "No PCI resources.\n");
		जाओ fail1;
	पूर्ण

	ret = velocity_probe(&pdev->dev, pdev->irq, info, BUS_PCI);
	अगर (ret == 0)
		वापस 0;

	pci_release_regions(pdev);
fail1:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम velocity_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	velocity_हटाओ(&pdev->dev);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक velocity_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा velocity_info_tbl *info;
	पूर्णांक irq;

	of_id = of_match_device(velocity_of_ids, &pdev->dev);
	अगर (!of_id)
		वापस -EINVAL;
	info = of_id->data;

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (!irq)
		वापस -EINVAL;

	वापस velocity_probe(&pdev->dev, irq, info, BUS_PLATFORM);
पूर्ण

अटल पूर्णांक velocity_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	velocity_हटाओ(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/**
 *	wol_calc_crc		-	WOL CRC
 *	@size: size of the wake mask
 *	@pattern: data pattern
 *	@mask_pattern: mask
 *
 *	Compute the wake on lan crc hashes क्रम the packet header
 *	we are पूर्णांकerested in.
 */
अटल u16 wol_calc_crc(पूर्णांक size, u8 *pattern, u8 *mask_pattern)
अणु
	u16 crc = 0xFFFF;
	u8 mask;
	पूर्णांक i, j;

	क्रम (i = 0; i < size; i++) अणु
		mask = mask_pattern[i];

		/* Skip this loop अगर the mask equals to zero */
		अगर (mask == 0x00)
			जारी;

		क्रम (j = 0; j < 8; j++) अणु
			अगर ((mask & 0x01) == 0) अणु
				mask >>= 1;
				जारी;
			पूर्ण
			mask >>= 1;
			crc = crc_ccitt(crc, &(pattern[i * 8 + j]), 1);
		पूर्ण
	पूर्ण
	/*	Finally, invert the result once to get the correct data */
	crc = ~crc;
	वापस bitrev32(crc) >> 16;
पूर्ण

/**
 *	velocity_set_wol	-	set up क्रम wake on lan
 *	@vptr: velocity to set WOL status on
 *
 *	Set a card up क्रम wake on lan either by unicast or by
 *	ARP packet.
 *
 *	FIXME: check अटल buffer is safe here
 */
अटल पूर्णांक velocity_set_wol(काष्ठा velocity_info *vptr)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	क्रमागत speed_opt spd_dpx = vptr->options.spd_dpx;
	अटल u8 buf[256];
	पूर्णांक i;

	अटल u32 mask_pattern[2][4] = अणु
		अणु0x00203000, 0x000003C0, 0x00000000, 0x0000000पूर्ण, /* ARP */
		अणु0xfffff000, 0xffffffff, 0xffffffff, 0x000ffffपूर्ण	 /* Magic Packet */
	पूर्ण;

	ग_लिखोw(0xFFFF, &regs->WOLCRClr);
	ग_लिखोb(WOLCFG_SAB | WOLCFG_SAM, &regs->WOLCFGSet);
	ग_लिखोw(WOLCR_MAGIC_EN, &regs->WOLCRSet);

	/*
	   अगर (vptr->wol_opts & VELOCITY_WOL_PHY)
	   ग_लिखोw((WOLCR_LINKON_EN|WOLCR_LINKOFF_EN), &regs->WOLCRSet);
	 */

	अगर (vptr->wol_opts & VELOCITY_WOL_UCAST)
		ग_लिखोw(WOLCR_UNICAST_EN, &regs->WOLCRSet);

	अगर (vptr->wol_opts & VELOCITY_WOL_ARP) अणु
		काष्ठा arp_packet *arp = (काष्ठा arp_packet *) buf;
		u16 crc;
		स_रखो(buf, 0, माप(काष्ठा arp_packet) + 7);

		क्रम (i = 0; i < 4; i++)
			ग_लिखोl(mask_pattern[0][i], &regs->ByteMask[0][i]);

		arp->type = htons(ETH_P_ARP);
		arp->ar_op = htons(1);

		स_नकल(arp->ar_tip, vptr->ip_addr, 4);

		crc = wol_calc_crc((माप(काष्ठा arp_packet) + 7) / 8, buf,
				(u8 *) & mask_pattern[0][0]);

		ग_लिखोw(crc, &regs->PatternCRC[0]);
		ग_लिखोw(WOLCR_ARP_EN, &regs->WOLCRSet);
	पूर्ण

	BYTE_REG_BITS_ON(PWCFG_WOLTYPE, &regs->PWCFGSet);
	BYTE_REG_BITS_ON(PWCFG_LEGACY_WOLEN, &regs->PWCFGSet);

	ग_लिखोw(0x0FFF, &regs->WOLSRClr);

	अगर (spd_dpx == SPD_DPX_1000_FULL)
		जाओ mac_करोne;

	अगर (spd_dpx != SPD_DPX_AUTO)
		जाओ advertise_करोne;

	अगर (vptr->mii_status & VELOCITY_AUTONEG_ENABLE) अणु
		अगर (PHYID_GET_PHY_ID(vptr->phy_id) == PHYID_CICADA_CS8201)
			MII_REG_BITS_ON(AUXCR_MDPPS, MII_NCONFIG, vptr->mac_regs);

		MII_REG_BITS_OFF(ADVERTISE_1000FULL | ADVERTISE_1000HALF, MII_CTRL1000, vptr->mac_regs);
	पूर्ण

	अगर (vptr->mii_status & VELOCITY_SPEED_1000)
		MII_REG_BITS_ON(BMCR_ANRESTART, MII_BMCR, vptr->mac_regs);

advertise_करोne:
	BYTE_REG_BITS_ON(CHIPGCR_FCMODE, &regs->CHIPGCR);

	अणु
		u8 GCR;
		GCR = पढ़ोb(&regs->CHIPGCR);
		GCR = (GCR & ~CHIPGCR_FCGMII) | CHIPGCR_FCFDX;
		ग_लिखोb(GCR, &regs->CHIPGCR);
	पूर्ण

mac_करोne:
	BYTE_REG_BITS_OFF(ISR_PWEI, &regs->ISR);
	/* Turn on SWPTAG just beक्रमe entering घातer mode */
	BYTE_REG_BITS_ON(STICKHW_SWPTAG, &regs->STICKHW);
	/* Go to bed ..... */
	BYTE_REG_BITS_ON((STICKHW_DS1 | STICKHW_DS0), &regs->STICKHW);

	वापस 0;
पूर्ण

/**
 *	velocity_save_context	-	save रेजिस्टरs
 *	@vptr: velocity
 *	@context: buffer क्रम stored context
 *
 *	Retrieve the current configuration from the velocity hardware
 *	and stash it in the context काष्ठाure, क्रम use by the context
 *	restore functions. This allows us to save things we need across
 *	घातer करोwn states
 */
अटल व्योम velocity_save_context(काष्ठा velocity_info *vptr, काष्ठा velocity_context *context)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	u16 i;
	u8 __iomem *ptr = (u8 __iomem *)regs;

	क्रम (i = MAC_REG_PAR; i < MAC_REG_CR0_CLR; i += 4)
		*((u32 *) (context->mac_reg + i)) = पढ़ोl(ptr + i);

	क्रम (i = MAC_REG_MAR; i < MAC_REG_TDCSR_CLR; i += 4)
		*((u32 *) (context->mac_reg + i)) = पढ़ोl(ptr + i);

	क्रम (i = MAC_REG_RDBASE_LO; i < MAC_REG_FIFO_TEST0; i += 4)
		*((u32 *) (context->mac_reg + i)) = पढ़ोl(ptr + i);

पूर्ण

अटल पूर्णांक velocity_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा velocity_info *vptr = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running(vptr->netdev))
		वापस 0;

	netअगर_device_detach(vptr->netdev);

	spin_lock_irqsave(&vptr->lock, flags);
	अगर (vptr->pdev)
		pci_save_state(vptr->pdev);

	अगर (vptr->flags & VELOCITY_FLAGS_WOL_ENABLED) अणु
		velocity_get_ip(vptr);
		velocity_save_context(vptr, &vptr->context);
		velocity_shutकरोwn(vptr);
		velocity_set_wol(vptr);
		अगर (vptr->pdev)
			pci_enable_wake(vptr->pdev, PCI_D3hot, 1);
		velocity_set_घातer_state(vptr, PCI_D3hot);
	पूर्ण अन्यथा अणु
		velocity_save_context(vptr, &vptr->context);
		velocity_shutकरोwn(vptr);
		अगर (vptr->pdev)
			pci_disable_device(vptr->pdev);
		velocity_set_घातer_state(vptr, PCI_D3hot);
	पूर्ण

	spin_unlock_irqrestore(&vptr->lock, flags);
	वापस 0;
पूर्ण

/**
 *	velocity_restore_context	-	restore रेजिस्टरs
 *	@vptr: velocity
 *	@context: buffer क्रम stored context
 *
 *	Reload the रेजिस्टर configuration from the velocity context
 *	created by velocity_save_context.
 */
अटल व्योम velocity_restore_context(काष्ठा velocity_info *vptr, काष्ठा velocity_context *context)
अणु
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	पूर्णांक i;
	u8 __iomem *ptr = (u8 __iomem *)regs;

	क्रम (i = MAC_REG_PAR; i < MAC_REG_CR0_SET; i += 4)
		ग_लिखोl(*((u32 *) (context->mac_reg + i)), ptr + i);

	/* Just skip cr0 */
	क्रम (i = MAC_REG_CR1_SET; i < MAC_REG_CR0_CLR; i++) अणु
		/* Clear */
		ग_लिखोb(~(*((u8 *) (context->mac_reg + i))), ptr + i + 4);
		/* Set */
		ग_लिखोb(*((u8 *) (context->mac_reg + i)), ptr + i);
	पूर्ण

	क्रम (i = MAC_REG_MAR; i < MAC_REG_IMR; i += 4)
		ग_लिखोl(*((u32 *) (context->mac_reg + i)), ptr + i);

	क्रम (i = MAC_REG_RDBASE_LO; i < MAC_REG_FIFO_TEST0; i += 4)
		ग_लिखोl(*((u32 *) (context->mac_reg + i)), ptr + i);

	क्रम (i = MAC_REG_TDCSR_SET; i <= MAC_REG_RDCSR_SET; i++)
		ग_लिखोb(*((u8 *) (context->mac_reg + i)), ptr + i);
पूर्ण

अटल पूर्णांक velocity_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा velocity_info *vptr = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (!netअगर_running(vptr->netdev))
		वापस 0;

	velocity_set_घातer_state(vptr, PCI_D0);

	अगर (vptr->pdev) अणु
		pci_enable_wake(vptr->pdev, PCI_D0, 0);
		pci_restore_state(vptr->pdev);
	पूर्ण

	mac_wol_reset(vptr->mac_regs);

	spin_lock_irqsave(&vptr->lock, flags);
	velocity_restore_context(vptr, &vptr->context);
	velocity_init_रेजिस्टरs(vptr, VELOCITY_INIT_WOL);
	mac_disable_पूर्णांक(vptr->mac_regs);

	velocity_tx_srv(vptr);

	क्रम (i = 0; i < vptr->tx.numq; i++) अणु
		अगर (vptr->tx.used[i])
			mac_tx_queue_wake(vptr->mac_regs, i);
	पूर्ण

	mac_enable_पूर्णांक(vptr->mac_regs);
	spin_unlock_irqrestore(&vptr->lock, flags);
	netअगर_device_attach(vptr->netdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(velocity_pm_ops, velocity_suspend, velocity_resume);

/*
 *	Definition क्रम our device driver. The PCI layer पूर्णांकerface
 *	uses this to handle all our card discover and plugging
 */
अटल काष्ठा pci_driver velocity_pci_driver = अणु
	.name		= VELOCITY_NAME,
	.id_table	= velocity_pci_id_table,
	.probe		= velocity_pci_probe,
	.हटाओ		= velocity_pci_हटाओ,
	.driver = अणु
		.pm = &velocity_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver velocity_platक्रमm_driver = अणु
	.probe		= velocity_platक्रमm_probe,
	.हटाओ		= velocity_platक्रमm_हटाओ,
	.driver = अणु
		.name = "via-velocity",
		.of_match_table = velocity_of_ids,
		.pm = &velocity_pm_ops,
	पूर्ण,
पूर्ण;

/**
 *	velocity_ethtool_up	-	pre hook क्रम ethtool
 *	@dev: network device
 *
 *	Called beक्रमe an ethtool operation. We need to make sure the
 *	chip is out of D3 state beक्रमe we poke at it. In हाल of ethtool
 *	ops nesting, only wake the device up in the outermost block.
 */
अटल पूर्णांक velocity_ethtool_up(काष्ठा net_device *dev)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	अगर (vptr->ethtool_ops_nesting == U32_MAX)
		वापस -EBUSY;
	अगर (!vptr->ethtool_ops_nesting++ && !netअगर_running(dev))
		velocity_set_घातer_state(vptr, PCI_D0);
	वापस 0;
पूर्ण

/**
 *	velocity_ethtool_करोwn	-	post hook क्रम ethtool
 *	@dev: network device
 *
 *	Called after an ethtool operation. Restore the chip back to D3
 *	state अगर it isn't running. In हाल of ethtool ops nesting, only
 *	put the device to sleep in the outermost block.
 */
अटल व्योम velocity_ethtool_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	अगर (!--vptr->ethtool_ops_nesting && !netअगर_running(dev))
		velocity_set_घातer_state(vptr, PCI_D3hot);
पूर्ण

अटल पूर्णांक velocity_get_link_ksettings(काष्ठा net_device *dev,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	काष्ठा mac_regs __iomem *regs = vptr->mac_regs;
	u32 status;
	u32 supported, advertising;

	status = check_connection_type(vptr->mac_regs);

	supported = SUPPORTED_TP |
			SUPPORTED_Autoneg |
			SUPPORTED_10baseT_Half |
			SUPPORTED_10baseT_Full |
			SUPPORTED_100baseT_Half |
			SUPPORTED_100baseT_Full |
			SUPPORTED_1000baseT_Half |
			SUPPORTED_1000baseT_Full;

	advertising = ADVERTISED_TP | ADVERTISED_Autoneg;
	अगर (vptr->options.spd_dpx == SPD_DPX_AUTO) अणु
		advertising |=
			ADVERTISED_10baseT_Half |
			ADVERTISED_10baseT_Full |
			ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full |
			ADVERTISED_1000baseT_Half |
			ADVERTISED_1000baseT_Full;
	पूर्ण अन्यथा अणु
		चयन (vptr->options.spd_dpx) अणु
		हाल SPD_DPX_1000_FULL:
			advertising |= ADVERTISED_1000baseT_Full;
			अवरोध;
		हाल SPD_DPX_100_HALF:
			advertising |= ADVERTISED_100baseT_Half;
			अवरोध;
		हाल SPD_DPX_100_FULL:
			advertising |= ADVERTISED_100baseT_Full;
			अवरोध;
		हाल SPD_DPX_10_HALF:
			advertising |= ADVERTISED_10baseT_Half;
			अवरोध;
		हाल SPD_DPX_10_FULL:
			advertising |= ADVERTISED_10baseT_Full;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status & VELOCITY_SPEED_1000)
		cmd->base.speed = SPEED_1000;
	अन्यथा अगर (status & VELOCITY_SPEED_100)
		cmd->base.speed = SPEED_100;
	अन्यथा
		cmd->base.speed = SPEED_10;

	cmd->base.स्वतःneg = (status & VELOCITY_AUTONEG_ENABLE) ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;
	cmd->base.port = PORT_TP;
	cmd->base.phy_address = पढ़ोb(&regs->MIIADR) & 0x1F;

	अगर (status & VELOCITY_DUPLEX_FULL)
		cmd->base.duplex = DUPLEX_FULL;
	अन्यथा
		cmd->base.duplex = DUPLEX_HALF;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक velocity_set_link_ksettings(काष्ठा net_device *dev,
				       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	u32 curr_status;
	u32 new_status = 0;
	पूर्णांक ret = 0;

	curr_status = check_connection_type(vptr->mac_regs);
	curr_status &= (~VELOCITY_LINK_FAIL);

	new_status |= ((cmd->base.स्वतःneg) ? VELOCITY_AUTONEG_ENABLE : 0);
	new_status |= ((speed == SPEED_1000) ? VELOCITY_SPEED_1000 : 0);
	new_status |= ((speed == SPEED_100) ? VELOCITY_SPEED_100 : 0);
	new_status |= ((speed == SPEED_10) ? VELOCITY_SPEED_10 : 0);
	new_status |= ((cmd->base.duplex == DUPLEX_FULL) ?
		       VELOCITY_DUPLEX_FULL : 0);

	अगर ((new_status & VELOCITY_AUTONEG_ENABLE) &&
	    (new_status != (curr_status | VELOCITY_AUTONEG_ENABLE))) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		क्रमागत speed_opt spd_dpx;

		अगर (new_status & VELOCITY_AUTONEG_ENABLE)
			spd_dpx = SPD_DPX_AUTO;
		अन्यथा अगर ((new_status & VELOCITY_SPEED_1000) &&
			 (new_status & VELOCITY_DUPLEX_FULL)) अणु
			spd_dpx = SPD_DPX_1000_FULL;
		पूर्ण अन्यथा अगर (new_status & VELOCITY_SPEED_100)
			spd_dpx = (new_status & VELOCITY_DUPLEX_FULL) ?
				SPD_DPX_100_FULL : SPD_DPX_100_HALF;
		अन्यथा अगर (new_status & VELOCITY_SPEED_10)
			spd_dpx = (new_status & VELOCITY_DUPLEX_FULL) ?
				SPD_DPX_10_FULL : SPD_DPX_10_HALF;
		अन्यथा
			वापस -EOPNOTSUPP;

		vptr->options.spd_dpx = spd_dpx;

		velocity_set_media_mode(vptr, new_status);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम velocity_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	strlcpy(info->driver, VELOCITY_NAME, माप(info->driver));
	strlcpy(info->version, VELOCITY_VERSION, माप(info->version));
	अगर (vptr->pdev)
		strlcpy(info->bus_info, pci_name(vptr->pdev),
						माप(info->bus_info));
	अन्यथा
		strlcpy(info->bus_info, "platform", माप(info->bus_info));
पूर्ण

अटल व्योम velocity_ethtool_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	wol->supported = WAKE_PHY | WAKE_MAGIC | WAKE_UCAST | WAKE_ARP;
	wol->wolopts |= WAKE_MAGIC;
	/*
	   अगर (vptr->wol_opts & VELOCITY_WOL_PHY)
		   wol.wolopts|=WAKE_PHY;
			 */
	अगर (vptr->wol_opts & VELOCITY_WOL_UCAST)
		wol->wolopts |= WAKE_UCAST;
	अगर (vptr->wol_opts & VELOCITY_WOL_ARP)
		wol->wolopts |= WAKE_ARP;
	स_नकल(&wol->sopass, vptr->wol_passwd, 6);
पूर्ण

अटल पूर्णांक velocity_ethtool_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	अगर (!(wol->wolopts & (WAKE_PHY | WAKE_MAGIC | WAKE_UCAST | WAKE_ARP)))
		वापस -EFAULT;
	vptr->wol_opts = VELOCITY_WOL_MAGIC;

	/*
	   अगर (wol.wolopts & WAKE_PHY) अणु
	   vptr->wol_opts|=VELOCITY_WOL_PHY;
	   vptr->flags |=VELOCITY_FLAGS_WOL_ENABLED;
	   पूर्ण
	 */

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		vptr->wol_opts |= VELOCITY_WOL_MAGIC;
		vptr->flags |= VELOCITY_FLAGS_WOL_ENABLED;
	पूर्ण
	अगर (wol->wolopts & WAKE_UCAST) अणु
		vptr->wol_opts |= VELOCITY_WOL_UCAST;
		vptr->flags |= VELOCITY_FLAGS_WOL_ENABLED;
	पूर्ण
	अगर (wol->wolopts & WAKE_ARP) अणु
		vptr->wol_opts |= VELOCITY_WOL_ARP;
		vptr->flags |= VELOCITY_FLAGS_WOL_ENABLED;
	पूर्ण
	स_नकल(vptr->wol_passwd, wol->sopass, 6);
	वापस 0;
पूर्ण

अटल पूर्णांक get_pending_समयr_val(पूर्णांक val)
अणु
	पूर्णांक mult_bits = val >> 6;
	पूर्णांक mult = 1;

	चयन (mult_bits)
	अणु
	हाल 1:
		mult = 4; अवरोध;
	हाल 2:
		mult = 16; अवरोध;
	हाल 3:
		mult = 64; अवरोध;
	हाल 0:
	शेष:
		अवरोध;
	पूर्ण

	वापस (val & 0x3f) * mult;
पूर्ण

अटल व्योम set_pending_समयr_val(पूर्णांक *val, u32 us)
अणु
	u8 mult = 0;
	u8 shअगरt = 0;

	अगर (us >= 0x3f) अणु
		mult = 1; /* mult with 4 */
		shअगरt = 2;
	पूर्ण
	अगर (us >= 0x3f * 4) अणु
		mult = 2; /* mult with 16 */
		shअगरt = 4;
	पूर्ण
	अगर (us >= 0x3f * 16) अणु
		mult = 3; /* mult with 64 */
		shअगरt = 6;
	पूर्ण

	*val = (mult << 6) | ((us >> shअगरt) & 0x3f);
पूर्ण


अटल पूर्णांक velocity_get_coalesce(काष्ठा net_device *dev,
		काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);

	ecmd->tx_max_coalesced_frames = vptr->options.tx_पूर्णांकsup;
	ecmd->rx_max_coalesced_frames = vptr->options.rx_पूर्णांकsup;

	ecmd->rx_coalesce_usecs = get_pending_समयr_val(vptr->options.rxqueue_समयr);
	ecmd->tx_coalesce_usecs = get_pending_समयr_val(vptr->options.txqueue_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक velocity_set_coalesce(काष्ठा net_device *dev,
		काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा velocity_info *vptr = netdev_priv(dev);
	पूर्णांक max_us = 0x3f * 64;
	अचिन्हित दीर्घ flags;

	/* 6 bits of  */
	अगर (ecmd->tx_coalesce_usecs > max_us)
		वापस -EINVAL;
	अगर (ecmd->rx_coalesce_usecs > max_us)
		वापस -EINVAL;

	अगर (ecmd->tx_max_coalesced_frames > 0xff)
		वापस -EINVAL;
	अगर (ecmd->rx_max_coalesced_frames > 0xff)
		वापस -EINVAL;

	vptr->options.rx_पूर्णांकsup = ecmd->rx_max_coalesced_frames;
	vptr->options.tx_पूर्णांकsup = ecmd->tx_max_coalesced_frames;

	set_pending_समयr_val(&vptr->options.rxqueue_समयr,
			ecmd->rx_coalesce_usecs);
	set_pending_समयr_val(&vptr->options.txqueue_समयr,
			ecmd->tx_coalesce_usecs);

	/* Setup the पूर्णांकerrupt suppression and queue समयrs */
	spin_lock_irqsave(&vptr->lock, flags);
	mac_disable_पूर्णांक(vptr->mac_regs);
	setup_adaptive_पूर्णांकerrupts(vptr);
	setup_queue_समयrs(vptr);

	mac_ग_लिखो_पूर्णांक_mask(vptr->पूर्णांक_mask, vptr->mac_regs);
	mac_clear_isr(vptr->mac_regs);
	mac_enable_पूर्णांक(vptr->mac_regs);
	spin_unlock_irqrestore(&vptr->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर velocity_gstrings[][ETH_GSTRING_LEN] = अणु
	"rx_all",
	"rx_ok",
	"tx_ok",
	"rx_error",
	"rx_runt_ok",
	"rx_runt_err",
	"rx_64",
	"tx_64",
	"rx_65_to_127",
	"tx_65_to_127",
	"rx_128_to_255",
	"tx_128_to_255",
	"rx_256_to_511",
	"tx_256_to_511",
	"rx_512_to_1023",
	"tx_512_to_1023",
	"rx_1024_to_1518",
	"tx_1024_to_1518",
	"tx_ether_collisions",
	"rx_crc_errors",
	"rx_jumbo",
	"tx_jumbo",
	"rx_mac_control_frames",
	"tx_mac_control_frames",
	"rx_frame_alignment_errors",
	"rx_long_ok",
	"rx_long_err",
	"tx_sqe_errors",
	"rx_no_buf",
	"rx_symbol_errors",
	"in_range_length_errors",
	"late_collisions"
पूर्ण;

अटल व्योम velocity_get_strings(काष्ठा net_device *dev, u32 sset, u8 *data)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, *velocity_gstrings, माप(velocity_gstrings));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक velocity_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(velocity_gstrings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम velocity_get_ethtool_stats(काष्ठा net_device *dev,
				       काष्ठा ethtool_stats *stats, u64 *data)
अणु
	अगर (netअगर_running(dev)) अणु
		काष्ठा velocity_info *vptr = netdev_priv(dev);
		u32 *p = vptr->mib_counter;
		पूर्णांक i;

		spin_lock_irq(&vptr->lock);
		velocity_update_hw_mibs(vptr);
		spin_unlock_irq(&vptr->lock);

		क्रम (i = 0; i < ARRAY_SIZE(velocity_gstrings); i++)
			*data++ = *p++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops velocity_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo		= velocity_get_drvinfo,
	.get_wol		= velocity_ethtool_get_wol,
	.set_wol		= velocity_ethtool_set_wol,
	.get_link		= velocity_get_link,
	.get_strings		= velocity_get_strings,
	.get_sset_count		= velocity_get_sset_count,
	.get_ethtool_stats	= velocity_get_ethtool_stats,
	.get_coalesce		= velocity_get_coalesce,
	.set_coalesce		= velocity_set_coalesce,
	.begin			= velocity_ethtool_up,
	.complete		= velocity_ethtool_करोwn,
	.get_link_ksettings	= velocity_get_link_ksettings,
	.set_link_ksettings	= velocity_set_link_ksettings,
पूर्ण;

#अगर defined(CONFIG_PM) && defined(CONFIG_INET)
अटल पूर्णांक velocity_netdev_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ notअगरication, व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = ptr;
	काष्ठा net_device *dev = अगरa->अगरa_dev->dev;

	अगर (dev_net(dev) == &init_net &&
	    dev->netdev_ops == &velocity_netdev_ops)
		velocity_get_ip(netdev_priv(dev));

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block velocity_inetaddr_notअगरier = अणु
	.notअगरier_call	= velocity_netdev_event,
पूर्ण;

अटल व्योम velocity_रेजिस्टर_notअगरier(व्योम)
अणु
	रेजिस्टर_inetaddr_notअगरier(&velocity_inetaddr_notअगरier);
पूर्ण

अटल व्योम velocity_unरेजिस्टर_notअगरier(व्योम)
अणु
	unरेजिस्टर_inetaddr_notअगरier(&velocity_inetaddr_notअगरier);
पूर्ण

#अन्यथा

#घोषणा velocity_रेजिस्टर_notअगरier()	करो अणुपूर्ण जबतक (0)
#घोषणा velocity_unरेजिस्टर_notअगरier()	करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर	/* defined(CONFIG_PM) && defined(CONFIG_INET) */

/**
 *	velocity_init_module	-	load समय function
 *
 *	Called when the velocity module is loaded. The PCI driver
 *	is रेजिस्टरed with the PCI layer, and in turn will call
 *	the probe functions क्रम each velocity adapter installed
 *	in the प्रणाली.
 */
अटल पूर्णांक __init velocity_init_module(व्योम)
अणु
	पूर्णांक ret_pci, ret_platक्रमm;

	velocity_रेजिस्टर_notअगरier();

	ret_pci = pci_रेजिस्टर_driver(&velocity_pci_driver);
	ret_platक्रमm = platक्रमm_driver_रेजिस्टर(&velocity_platक्रमm_driver);

	/* अगर both_रेजिस्टरs failed, हटाओ the notअगरier */
	अगर ((ret_pci < 0) && (ret_platक्रमm < 0)) अणु
		velocity_unरेजिस्टर_notअगरier();
		वापस ret_pci;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	velocity_cleanup	-	module unload
 *
 *	When the velocity hardware is unloaded this function is called.
 *	It will clean up the notअगरiers and the unरेजिस्टर the PCI
 *	driver पूर्णांकerface क्रम this hardware. This in turn cleans up
 *	all discovered पूर्णांकerfaces beक्रमe वापसing from the function
 */
अटल व्योम __निकास velocity_cleanup_module(व्योम)
अणु
	velocity_unरेजिस्टर_notअगरier();

	pci_unरेजिस्टर_driver(&velocity_pci_driver);
	platक्रमm_driver_unरेजिस्टर(&velocity_platक्रमm_driver);
पूर्ण

module_init(velocity_init_module);
module_निकास(velocity_cleanup_module);
