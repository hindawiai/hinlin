<शैली गुरु>
/*
 * Radisys 82600 Embedded chipset Memory Controller kernel module
 * (C) 2005 EADS Astrium
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Tim Small <tim@buttersideup.com>, based on work by Thayne
 * Harbaugh, Dan Hollis <goemon at anime करोt net> and others.
 *
 * $Id: edac_r82600.c,v 1.1.2.6 2005/10/05 00:43:44 dsp_llnl Exp $
 *
 * Written with reference to 82600 High Integration Dual PCI System
 * Controller Data Book:
 * www.radisys.com/files/support_करोwnloads/007-01277-0002.82600DataBook.pdf
 * references to this करोcument given in []
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR	"r82600_edac"

#घोषणा r82600_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "r82600", fmt, ##arg)

#घोषणा r82600_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "r82600", fmt, ##arg)

/* Radisys say "The 82600 पूर्णांकegrates a मुख्य memory SDRAM controller that
 * supports up to four banks of memory. The four banks can support a mix of
 * sizes of 64 bit wide (72 bits with ECC) Synchronous DRAM (SDRAM) DIMMs,
 * each of which can be any size from 16MB to 512MB. Both रेजिस्टरed (control
 * संकेतs buffered) and unbuffered DIMM types are supported. Mixing of
 * रेजिस्टरed and unbuffered DIMMs as well as mixing of ECC and non-ECC DIMMs
 * is not allowed. The 82600 SDRAM पूर्णांकerface operates at the same frequency as
 * the CPU bus, 66MHz, 100MHz or 133MHz."
 */

#घोषणा R82600_NR_CSROWS 4
#घोषणा R82600_NR_CHANS  1
#घोषणा R82600_NR_DIMMS  4

#घोषणा R82600_BRIDGE_ID  0x8200

/* Radisys 82600 रेजिस्टर addresses - device 0 function 0 - PCI bridge */
#घोषणा R82600_DRAMC	0x57	/* Various SDRAM related control bits
				 * all bits are R/W
				 *
				 * 7    SDRAM ISA Hole Enable
				 * 6    Flash Page Mode Enable
				 * 5    ECC Enable: 1=ECC 0=noECC
				 * 4    DRAM DIMM Type: 1=
				 * 3    BIOS Alias Disable
				 * 2    SDRAM BIOS Flash Write Enable
				 * 1:0  SDRAM Refresh Rate: 00=Disabled
				 *          01=7.8usec (256Mbit SDRAMs)
				 *          10=15.6us 11=125usec
				 */

#घोषणा R82600_SDRAMC	0x76	/* "SDRAM Control Register"
				 * More SDRAM related control bits
				 * all bits are R/W
				 *
				 * 15:8 Reserved.
				 *
				 * 7:5  Special SDRAM Mode Select
				 *
				 * 4    Force ECC
				 *
				 *        1=Drive ECC bits to 0 during
				 *          ग_लिखो cycles (i.e. ECC test mode)
				 *
				 *        0=Normal ECC functioning
				 *
				 * 3    Enhanced Paging Enable
				 *
				 * 2    CAS# Latency 0=3clks 1=2clks
				 *
				 * 1    RAS# to CAS# Delay 0=3 1=2
				 *
				 * 0    RAS# Preअक्षरge     0=3 1=2
				 */

#घोषणा R82600_EAP	0x80	/* ECC Error Address Poपूर्णांकer Register
				 *
				 * 31    Disable Hardware Scrubbing (RW)
				 *        0=Scrub on corrected पढ़ो
				 *        1=Don't scrub on corrected पढ़ो
				 *
				 * 30:12 Error Address Poपूर्णांकer (RO)
				 *        Upper 19 bits of error address
				 *
				 * 11:4  Syndrome Bits (RO)
				 *
				 * 3     BSERR# on multibit error (RW)
				 *        1=enable 0=disable
				 *
				 * 2     NMI on Single Bit Eror (RW)
				 *        1=NMI triggered by SBE n.b. other
				 *          prerequeists
				 *        0=NMI not triggered
				 *
				 * 1     MBE (R/WC)
				 *        पढ़ो 1=MBE at EAP (see above)
				 *        पढ़ो 0=no MBE, or SBE occurred first
				 *        ग_लिखो 1=Clear MBE status (must also
				 *          clear SBE)
				 *        ग_लिखो 0=NOP
				 *
				 * 1     SBE (R/WC)
				 *        पढ़ो 1=SBE at EAP (see above)
				 *        पढ़ो 0=no SBE, or MBE occurred first
				 *        ग_लिखो 1=Clear SBE status (must also
				 *          clear MBE)
				 *        ग_लिखो 0=NOP
				 */

#घोषणा R82600_DRBA	0x60	/* + 0x60..0x63 SDRAM Row Boundary Address
				 *  Registers
				 *
				 * 7:0  Address lines 30:24 - upper limit of
				 * each row [p57]
				 */

काष्ठा r82600_error_info अणु
	u32 eapr;
पूर्ण;

अटल bool disable_hardware_scrub;

अटल काष्ठा edac_pci_ctl_info *r82600_pci;

अटल व्योम r82600_get_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा r82600_error_info *info)
अणु
	काष्ठा pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);
	pci_पढ़ो_config_dword(pdev, R82600_EAP, &info->eapr);

	अगर (info->eapr & BIT(0))
		/* Clear error to allow next error to be reported [p.62] */
		pci_ग_लिखो_bits32(pdev, R82600_EAP,
				 ((u32) BIT(0) & (u32) BIT(1)),
				 ((u32) BIT(0) & (u32) BIT(1)));

	अगर (info->eapr & BIT(1))
		/* Clear error to allow next error to be reported [p.62] */
		pci_ग_लिखो_bits32(pdev, R82600_EAP,
				 ((u32) BIT(0) & (u32) BIT(1)),
				 ((u32) BIT(0) & (u32) BIT(1)));
पूर्ण

अटल पूर्णांक r82600_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा r82600_error_info *info,
				पूर्णांक handle_errors)
अणु
	पूर्णांक error_found;
	u32 eapaddr, page;
	u32 syndrome;

	error_found = 0;

	/* bits 30:12 store the upper 19 bits of the 32 bit error address */
	eapaddr = ((info->eapr >> 12) & 0x7FFF) << 13;
	/* Syndrome in bits 11:4 [p.62]       */
	syndrome = (info->eapr >> 4) & 0xFF;

	/* the R82600 reports at less than page *
	 * granularity (upper 19 bits only)     */
	page = eapaddr >> PAGE_SHIFT;

	अगर (info->eapr & BIT(0)) अणु	/* CE? */
		error_found = 1;

		अगर (handle_errors)
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     page, 0, syndrome,
					     edac_mc_find_csrow_by_page(mci, page),
					     0, -1,
					     mci->ctl_name, "");
	पूर्ण

	अगर (info->eapr & BIT(1)) अणु	/* UE? */
		error_found = 1;

		अगर (handle_errors)
			/* 82600 करोesn't give enough info */
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     page, 0, 0,
					     edac_mc_find_csrow_by_page(mci, page),
					     0, -1,
					     mci->ctl_name, "");
	पूर्ण

	वापस error_found;
पूर्ण

अटल व्योम r82600_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा r82600_error_info info;

	r82600_get_error_info(mci, &info);
	r82600_process_error_info(mci, &info, 1);
पूर्ण

अटल अंतरभूत पूर्णांक ecc_enabled(u8 dramcr)
अणु
	वापस dramcr & BIT(5);
पूर्ण

अटल व्योम r82600_init_csrows(काष्ठा mem_ctl_info *mci, काष्ठा pci_dev *pdev,
			u8 dramcr)
अणु
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	पूर्णांक index;
	u8 drbar;		/* SDRAM Row Boundary Address Register */
	u32 row_high_limit, row_high_limit_last;
	u32 reg_sdram, ecc_on, row_base;

	ecc_on = ecc_enabled(dramcr);
	reg_sdram = dramcr & BIT(4);
	row_high_limit_last = 0;

	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		/* find the DRAM Chip Select Base address and mask */
		pci_पढ़ो_config_byte(pdev, R82600_DRBA + index, &drbar);

		edac_dbg(1, "Row=%d DRBA = %#0x\n", index, drbar);

		row_high_limit = ((u32) drbar << 24);
/*		row_high_limit = ((u32)drbar << 24) | 0xffffffUL; */

		edac_dbg(1, "Row=%d, Boundary Address=%#0x, Last = %#0x\n",
			 index, row_high_limit, row_high_limit_last);

		/* Empty row [p.57] */
		अगर (row_high_limit == row_high_limit_last)
			जारी;

		row_base = row_high_limit_last;

		csrow->first_page = row_base >> PAGE_SHIFT;
		csrow->last_page = (row_high_limit >> PAGE_SHIFT) - 1;

		dimm->nr_pages = csrow->last_page - csrow->first_page + 1;
		/* Error address is top 19 bits - so granularity is      *
		 * 14 bits                                               */
		dimm->grain = 1 << 14;
		dimm->mtype = reg_sdram ? MEM_RDDR : MEM_DDR;
		/* FIXME - check that this is unknowable with this chipset */
		dimm->dtype = DEV_UNKNOWN;

		/* Mode is global on 82600 */
		dimm->edac_mode = ecc_on ? EDAC_SECDED : EDAC_NONE;
		row_high_limit_last = row_high_limit;
	पूर्ण
पूर्ण

अटल पूर्णांक r82600_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	u8 dramcr;
	u32 eapr;
	u32 scrub_disabled;
	u32 sdram_refresh_rate;
	काष्ठा r82600_error_info discard;

	edac_dbg(0, "\n");
	pci_पढ़ो_config_byte(pdev, R82600_DRAMC, &dramcr);
	pci_पढ़ो_config_dword(pdev, R82600_EAP, &eapr);
	scrub_disabled = eapr & BIT(31);
	sdram_refresh_rate = dramcr & (BIT(0) | BIT(1));
	edac_dbg(2, "sdram refresh rate = %#0x\n", sdram_refresh_rate);
	edac_dbg(2, "DRAMC register = %#0x\n", dramcr);
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = R82600_NR_CSROWS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = R82600_NR_CHANS;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, 0);
	अगर (mci == शून्य)
		वापस -ENOMEM;

	edac_dbg(0, "mci = %p\n", mci);
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_RDDR | MEM_FLAG_DDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_EC | EDAC_FLAG_SECDED;
	/* FIXME try to work out अगर the chip leads have been used क्रम COM2
	 * instead on this board? [MA6?] MAYBE:
	 */

	/* On the R82600, the pins क्रम memory bits 72:65 - i.e. the   *
	 * EC bits are shared with the pins क्रम COM2 (!), so अगर COM2  *
	 * is enabled, we assume COM2 is wired up, and thus no EDAC   *
	 * is possible.                                               */
	mci->edac_cap = EDAC_FLAG_NONE | EDAC_FLAG_EC | EDAC_FLAG_SECDED;

	अगर (ecc_enabled(dramcr)) अणु
		अगर (scrub_disabled)
			edac_dbg(3, "mci = %p - Scrubbing disabled! EAP: %#0x\n",
				 mci, eapr);
	पूर्ण अन्यथा
		mci->edac_cap = EDAC_FLAG_NONE;

	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = "R82600";
	mci->dev_name = pci_name(pdev);
	mci->edac_check = r82600_check;
	mci->ctl_page_to_phys = शून्य;
	r82600_init_csrows(mci, pdev, dramcr);
	r82600_get_error_info(mci, &discard);	/* clear counters */

	/* Here we assume that we will never see multiple instances of this
	 * type of memory controller.  The ID is thereक्रमe hardcoded to 0.
	 */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ fail;
	पूर्ण

	/* get this far and it's successful */

	अगर (disable_hardware_scrub) अणु
		edac_dbg(3, "Disabling Hardware Scrub (scrub on error)\n");
		pci_ग_लिखो_bits32(pdev, R82600_EAP, BIT(31), BIT(31));
	पूर्ण

	/* allocating generic PCI control info */
	r82600_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!r82600_pci) अणु
		prपूर्णांकk(KERN_WARNING
			"%s(): Unable to create PCI control\n",
			__func__);
		prपूर्णांकk(KERN_WARNING
			"%s(): PCI error report via EDAC not setup\n",
			__func__);
	पूर्ण

	edac_dbg(3, "success\n");
	वापस 0;

fail:
	edac_mc_मुक्त(mci);
	वापस -ENODEV;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक r82600_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	edac_dbg(0, "\n");

	/* करोn't need to call pci_enable_device() */
	वापस r82600_probe1(pdev, ent->driver_data);
पूर्ण

अटल व्योम r82600_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	अगर (r82600_pci)
		edac_pci_release_generic_ctl(r82600_pci);

	अगर ((mci = edac_mc_del_mc(&pdev->dev)) == शून्य)
		वापस;

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id r82600_pci_tbl[] = अणु
	अणु
	 PCI_DEVICE(PCI_VENDOR_ID_RADISYS, R82600_BRIDGE_ID)
	 पूर्ण,
	अणु
	 0,
	 पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, r82600_pci_tbl);

अटल काष्ठा pci_driver r82600_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = r82600_init_one,
	.हटाओ = r82600_हटाओ_one,
	.id_table = r82600_pci_tbl,
पूर्ण;

अटल पूर्णांक __init r82600_init(व्योम)
अणु
       /* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
       opstate_init();

	वापस pci_रेजिस्टर_driver(&r82600_driver);
पूर्ण

अटल व्योम __निकास r82600_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&r82600_driver);
पूर्ण

module_init(r82600_init);
module_निकास(r82600_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tim Small <tim@buttersideup.com> - WPAD Ltd. "
		"on behalf of EADS Astrium");
MODULE_DESCRIPTION("MC support for Radisys 82600 memory controllers");

module_param(disable_hardware_scrub, bool, 0644);
MODULE_PARM_DESC(disable_hardware_scrub,
		 "If set, disable the chipset's automatic scrub for CEs");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
