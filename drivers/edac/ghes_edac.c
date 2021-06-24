<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GHES/EDAC Linux driver
 *
 * Copyright (c) 2013 by Mauro Carvalho Chehab
 *
 * Red Hat Inc. https://www.redhat.com
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <acpi/ghes.h>
#समावेश <linux/edac.h>
#समावेश <linux/dmi.h>
#समावेश "edac_module.h"
#समावेश <ras/ras_event.h>

काष्ठा ghes_pvt अणु
	काष्ठा mem_ctl_info *mci;

	/* Buffers क्रम the error handling routine */
	अक्षर other_detail[400];
	अक्षर msg[80];
पूर्ण;

अटल refcount_t ghes_refcount = REFCOUNT_INIT(0);

/*
 * Access to ghes_pvt must be रक्षित by ghes_lock. The spinlock
 * also provides the necessary (implicit) memory barrier क्रम the SMP
 * हाल to make the poपूर्णांकer visible on another CPU.
 */
अटल काष्ठा ghes_pvt *ghes_pvt;

/*
 * This driver's representation of the प्रणाली hardware, as collected
 * from DMI.
 */
काष्ठा ghes_hw_desc अणु
	पूर्णांक num_dimms;
	काष्ठा dimm_info *dimms;
पूर्ण ghes_hw;

/* GHES registration mutex */
अटल DEFINE_MUTEX(ghes_reg_mutex);

/*
 * Sync with other, potentially concurrent callers of
 * ghes_edac_report_mem_error(). We करोn't know what the
 * "inventive" firmware would करो.
 */
अटल DEFINE_SPINLOCK(ghes_lock);

/* "ghes_edac.force_load=1" skips the platक्रमm check */
अटल bool __पढ़ो_mostly क्रमce_load;
module_param(क्रमce_load, bool, 0);

अटल bool प्रणाली_scanned;

/* Memory Device - Type 17 of SMBIOS spec */
काष्ठा memdev_dmi_entry अणु
	u8 type;
	u8 length;
	u16 handle;
	u16 phys_mem_array_handle;
	u16 mem_err_info_handle;
	u16 total_width;
	u16 data_width;
	u16 size;
	u8 क्रमm_factor;
	u8 device_set;
	u8 device_locator;
	u8 bank_locator;
	u8 memory_type;
	u16 type_detail;
	u16 speed;
	u8 manufacturer;
	u8 serial_number;
	u8 asset_tag;
	u8 part_number;
	u8 attributes;
	u32 extended_size;
	u16 conf_mem_clk_speed;
पूर्ण __attribute__((__packed__));

अटल काष्ठा dimm_info *find_dimm_by_handle(काष्ठा mem_ctl_info *mci, u16 handle)
अणु
	काष्ठा dimm_info *dimm;

	mci_क्रम_each_dimm(mci, dimm) अणु
		अगर (dimm->smbios_handle == handle)
			वापस dimm;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम dimm_setup_label(काष्ठा dimm_info *dimm, u16 handle)
अणु
	स्थिर अक्षर *bank = शून्य, *device = शून्य;

	dmi_memdev_name(handle, &bank, &device);

	/* both strings must be non-zero */
	अगर (bank && *bank && device && *device)
		snम_लिखो(dimm->label, माप(dimm->label), "%s %s", bank, device);
पूर्ण

अटल व्योम assign_dmi_dimm_info(काष्ठा dimm_info *dimm, काष्ठा memdev_dmi_entry *entry)
अणु
	u16 rdr_mask = BIT(7) | BIT(13);

	अगर (entry->size == 0xffff) अणु
		pr_info("Can't get DIMM%i size\n", dimm->idx);
		dimm->nr_pages = MiB_TO_PAGES(32);/* Unknown */
	पूर्ण अन्यथा अगर (entry->size == 0x7fff) अणु
		dimm->nr_pages = MiB_TO_PAGES(entry->extended_size);
	पूर्ण अन्यथा अणु
		अगर (entry->size & BIT(15))
			dimm->nr_pages = MiB_TO_PAGES((entry->size & 0x7fff) << 10);
		अन्यथा
			dimm->nr_pages = MiB_TO_PAGES(entry->size);
	पूर्ण

	चयन (entry->memory_type) अणु
	हाल 0x12:
		अगर (entry->type_detail & BIT(13))
			dimm->mtype = MEM_RDDR;
		अन्यथा
			dimm->mtype = MEM_DDR;
		अवरोध;
	हाल 0x13:
		अगर (entry->type_detail & BIT(13))
			dimm->mtype = MEM_RDDR2;
		अन्यथा
			dimm->mtype = MEM_DDR2;
		अवरोध;
	हाल 0x14:
		dimm->mtype = MEM_FB_DDR2;
		अवरोध;
	हाल 0x18:
		अगर (entry->type_detail & BIT(12))
			dimm->mtype = MEM_NVDIMM;
		अन्यथा अगर (entry->type_detail & BIT(13))
			dimm->mtype = MEM_RDDR3;
		अन्यथा
			dimm->mtype = MEM_DDR3;
		अवरोध;
	हाल 0x1a:
		अगर (entry->type_detail & BIT(12))
			dimm->mtype = MEM_NVDIMM;
		अन्यथा अगर (entry->type_detail & BIT(13))
			dimm->mtype = MEM_RDDR4;
		अन्यथा
			dimm->mtype = MEM_DDR4;
		अवरोध;
	शेष:
		अगर (entry->type_detail & BIT(6))
			dimm->mtype = MEM_RMBS;
		अन्यथा अगर ((entry->type_detail & rdr_mask) == rdr_mask)
			dimm->mtype = MEM_RDR;
		अन्यथा अगर (entry->type_detail & BIT(7))
			dimm->mtype = MEM_SDR;
		अन्यथा अगर (entry->type_detail & BIT(9))
			dimm->mtype = MEM_EDO;
		अन्यथा
			dimm->mtype = MEM_UNKNOWN;
	पूर्ण

	/*
	 * Actually, we can only detect अगर the memory has bits क्रम
	 * checksum or not
	 */
	अगर (entry->total_width == entry->data_width)
		dimm->edac_mode = EDAC_NONE;
	अन्यथा
		dimm->edac_mode = EDAC_SECDED;

	dimm->dtype = DEV_UNKNOWN;
	dimm->grain = 128;		/* Likely, worse हाल */

	dimm_setup_label(dimm, entry->handle);

	अगर (dimm->nr_pages) अणु
		edac_dbg(1, "DIMM%i: %s size = %d MB%s\n",
			dimm->idx, edac_mem_types[dimm->mtype],
			PAGES_TO_MiB(dimm->nr_pages),
			(dimm->edac_mode != EDAC_NONE) ? "(ECC)" : "");
		edac_dbg(2, "\ttype %d, detail 0x%02x, width %d(total %d)\n",
			entry->memory_type, entry->type_detail,
			entry->total_width, entry->data_width);
	पूर्ण

	dimm->smbios_handle = entry->handle;
पूर्ण

अटल व्योम क्रमागतerate_dimms(स्थिर काष्ठा dmi_header *dh, व्योम *arg)
अणु
	काष्ठा memdev_dmi_entry *entry = (काष्ठा memdev_dmi_entry *)dh;
	काष्ठा ghes_hw_desc *hw = (काष्ठा ghes_hw_desc *)arg;
	काष्ठा dimm_info *d;

	अगर (dh->type != DMI_ENTRY_MEM_DEVICE)
		वापस;

	/* Enlarge the array with additional 16 */
	अगर (!hw->num_dimms || !(hw->num_dimms % 16)) अणु
		काष्ठा dimm_info *new;

		new = kपुनः_स्मृति_array(hw->dimms, hw->num_dimms + 16,
				     माप(काष्ठा dimm_info), GFP_KERNEL);
		अगर (!new) अणु
			WARN_ON_ONCE(1);
			वापस;
		पूर्ण

		hw->dimms = new;
	पूर्ण

	d = &hw->dimms[hw->num_dimms];
	d->idx = hw->num_dimms;

	assign_dmi_dimm_info(d, entry);

	hw->num_dimms++;
पूर्ण

अटल व्योम ghes_scan_प्रणाली(व्योम)
अणु
	अगर (प्रणाली_scanned)
		वापस;

	dmi_walk(क्रमागतerate_dimms, &ghes_hw);

	प्रणाली_scanned = true;
पूर्ण

व्योम ghes_edac_report_mem_error(पूर्णांक sev, काष्ठा cper_sec_mem_err *mem_err)
अणु
	काष्ठा edac_raw_error_desc *e;
	काष्ठा mem_ctl_info *mci;
	काष्ठा ghes_pvt *pvt;
	अचिन्हित दीर्घ flags;
	अक्षर *p;

	/*
	 * We can करो the locking below because GHES defers error processing
	 * from NMI to IRQ context. Whenever that changes, we'd at least
	 * know.
	 */
	अगर (WARN_ON_ONCE(in_nmi()))
		वापस;

	spin_lock_irqsave(&ghes_lock, flags);

	pvt = ghes_pvt;
	अगर (!pvt)
		जाओ unlock;

	mci = pvt->mci;
	e = &mci->error_desc;

	/* Cleans the error report buffer */
	स_रखो(e, 0, माप (*e));
	e->error_count = 1;
	e->grain = 1;
	e->msg = pvt->msg;
	e->other_detail = pvt->other_detail;
	e->top_layer = -1;
	e->mid_layer = -1;
	e->low_layer = -1;
	*pvt->other_detail = '\0';
	*pvt->msg = '\0';

	चयन (sev) अणु
	हाल GHES_SEV_CORRECTED:
		e->type = HW_EVENT_ERR_CORRECTED;
		अवरोध;
	हाल GHES_SEV_RECOVERABLE:
		e->type = HW_EVENT_ERR_UNCORRECTED;
		अवरोध;
	हाल GHES_SEV_PANIC:
		e->type = HW_EVENT_ERR_FATAL;
		अवरोध;
	शेष:
	हाल GHES_SEV_NO:
		e->type = HW_EVENT_ERR_INFO;
	पूर्ण

	edac_dbg(1, "error validation_bits: 0x%08llx\n",
		 (दीर्घ दीर्घ)mem_err->validation_bits);

	/* Error type, mapped on e->msg */
	अगर (mem_err->validation_bits & CPER_MEM_VALID_ERROR_TYPE) अणु
		p = pvt->msg;
		चयन (mem_err->error_type) अणु
		हाल 0:
			p += प्र_लिखो(p, "Unknown");
			अवरोध;
		हाल 1:
			p += प्र_लिखो(p, "No error");
			अवरोध;
		हाल 2:
			p += प्र_लिखो(p, "Single-bit ECC");
			अवरोध;
		हाल 3:
			p += प्र_लिखो(p, "Multi-bit ECC");
			अवरोध;
		हाल 4:
			p += प्र_लिखो(p, "Single-symbol ChipKill ECC");
			अवरोध;
		हाल 5:
			p += प्र_लिखो(p, "Multi-symbol ChipKill ECC");
			अवरोध;
		हाल 6:
			p += प्र_लिखो(p, "Master abort");
			अवरोध;
		हाल 7:
			p += प्र_लिखो(p, "Target abort");
			अवरोध;
		हाल 8:
			p += प्र_लिखो(p, "Parity Error");
			अवरोध;
		हाल 9:
			p += प्र_लिखो(p, "Watchdog timeout");
			अवरोध;
		हाल 10:
			p += प्र_लिखो(p, "Invalid address");
			अवरोध;
		हाल 11:
			p += प्र_लिखो(p, "Mirror Broken");
			अवरोध;
		हाल 12:
			p += प्र_लिखो(p, "Memory Sparing");
			अवरोध;
		हाल 13:
			p += प्र_लिखो(p, "Scrub corrected error");
			अवरोध;
		हाल 14:
			p += प्र_लिखो(p, "Scrub uncorrected error");
			अवरोध;
		हाल 15:
			p += प्र_लिखो(p, "Physical Memory Map-out event");
			अवरोध;
		शेष:
			p += प्र_लिखो(p, "reserved error (%d)",
				     mem_err->error_type);
		पूर्ण
	पूर्ण अन्यथा अणु
		म_नकल(pvt->msg, "unknown error");
	पूर्ण

	/* Error address */
	अगर (mem_err->validation_bits & CPER_MEM_VALID_PA) अणु
		e->page_frame_number = PHYS_PFN(mem_err->physical_addr);
		e->offset_in_page = offset_in_page(mem_err->physical_addr);
	पूर्ण

	/* Error grain */
	अगर (mem_err->validation_bits & CPER_MEM_VALID_PA_MASK)
		e->grain = ~mem_err->physical_addr_mask + 1;

	/* Memory error location, mapped on e->location */
	p = e->location;
	अगर (mem_err->validation_bits & CPER_MEM_VALID_NODE)
		p += प्र_लिखो(p, "node:%d ", mem_err->node);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_CARD)
		p += प्र_लिखो(p, "card:%d ", mem_err->card);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_MODULE)
		p += प्र_लिखो(p, "module:%d ", mem_err->module);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_RANK_NUMBER)
		p += प्र_लिखो(p, "rank:%d ", mem_err->rank);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_BANK)
		p += प्र_लिखो(p, "bank:%d ", mem_err->bank);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_BANK_GROUP)
		p += प्र_लिखो(p, "bank_group:%d ",
			     mem_err->bank >> CPER_MEM_BANK_GROUP_SHIFT);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_BANK_ADDRESS)
		p += प्र_लिखो(p, "bank_address:%d ",
			     mem_err->bank & CPER_MEM_BANK_ADDRESS_MASK);
	अगर (mem_err->validation_bits & (CPER_MEM_VALID_ROW | CPER_MEM_VALID_ROW_EXT)) अणु
		u32 row = mem_err->row;

		row |= cper_get_mem_extension(mem_err->validation_bits, mem_err->extended);
		p += प्र_लिखो(p, "row:%d ", row);
	पूर्ण
	अगर (mem_err->validation_bits & CPER_MEM_VALID_COLUMN)
		p += प्र_लिखो(p, "col:%d ", mem_err->column);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_BIT_POSITION)
		p += प्र_लिखो(p, "bit_pos:%d ", mem_err->bit_pos);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_MODULE_HANDLE) अणु
		स्थिर अक्षर *bank = शून्य, *device = शून्य;
		काष्ठा dimm_info *dimm;

		dmi_memdev_name(mem_err->mem_dev_handle, &bank, &device);
		अगर (bank != शून्य && device != शून्य)
			p += प्र_लिखो(p, "DIMM location:%s %s ", bank, device);
		अन्यथा
			p += प्र_लिखो(p, "DIMM DMI handle: 0x%.4x ",
				     mem_err->mem_dev_handle);

		dimm = find_dimm_by_handle(mci, mem_err->mem_dev_handle);
		अगर (dimm) अणु
			e->top_layer = dimm->idx;
			म_नकल(e->label, dimm->label);
		पूर्ण
	पूर्ण
	अगर (mem_err->validation_bits & CPER_MEM_VALID_CHIP_ID)
		p += प्र_लिखो(p, "chipID: %d ",
			     mem_err->extended >> CPER_MEM_CHIP_ID_SHIFT);
	अगर (p > e->location)
		*(p - 1) = '\0';

	अगर (!*e->label)
		म_नकल(e->label, "unknown memory");

	/* All other fields are mapped on e->other_detail */
	p = pvt->other_detail;
	p += snम_लिखो(p, माप(pvt->other_detail),
		"APEI location: %s ", e->location);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_ERROR_STATUS) अणु
		u64 status = mem_err->error_status;

		p += प्र_लिखो(p, "status(0x%016llx): ", (दीर्घ दीर्घ)status);
		चयन ((status >> 8) & 0xff) अणु
		हाल 1:
			p += प्र_लिखो(p, "Error detected internal to the component ");
			अवरोध;
		हाल 16:
			p += प्र_लिखो(p, "Error detected in the bus ");
			अवरोध;
		हाल 4:
			p += प्र_लिखो(p, "Storage error in DRAM memory ");
			अवरोध;
		हाल 5:
			p += प्र_लिखो(p, "Storage error in TLB ");
			अवरोध;
		हाल 6:
			p += प्र_लिखो(p, "Storage error in cache ");
			अवरोध;
		हाल 7:
			p += प्र_लिखो(p, "Error in one or more functional units ");
			अवरोध;
		हाल 8:
			p += प्र_लिखो(p, "component failed self test ");
			अवरोध;
		हाल 9:
			p += प्र_लिखो(p, "Overflow or undervalue of internal queue ");
			अवरोध;
		हाल 17:
			p += प्र_लिखो(p, "Virtual address not found on IO-TLB or IO-PDIR ");
			अवरोध;
		हाल 18:
			p += प्र_लिखो(p, "Improper access error ");
			अवरोध;
		हाल 19:
			p += प्र_लिखो(p, "Access to a memory address which is not mapped to any component ");
			अवरोध;
		हाल 20:
			p += प्र_लिखो(p, "Loss of Lockstep ");
			अवरोध;
		हाल 21:
			p += प्र_लिखो(p, "Response not associated with a request ");
			अवरोध;
		हाल 22:
			p += प्र_लिखो(p, "Bus parity error - must also set the A, C, or D Bits ");
			अवरोध;
		हाल 23:
			p += प्र_लिखो(p, "Detection of a PATH_ERROR ");
			अवरोध;
		हाल 25:
			p += प्र_लिखो(p, "Bus operation timeout ");
			अवरोध;
		हाल 26:
			p += प्र_लिखो(p, "A read was issued to data that has been poisoned ");
			अवरोध;
		शेष:
			p += प्र_लिखो(p, "reserved ");
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (mem_err->validation_bits & CPER_MEM_VALID_REQUESTOR_ID)
		p += प्र_लिखो(p, "requestorID: 0x%016llx ",
			     (दीर्घ दीर्घ)mem_err->requestor_id);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_RESPONDER_ID)
		p += प्र_लिखो(p, "responderID: 0x%016llx ",
			     (दीर्घ दीर्घ)mem_err->responder_id);
	अगर (mem_err->validation_bits & CPER_MEM_VALID_TARGET_ID)
		p += प्र_लिखो(p, "targetID: 0x%016llx ",
			     (दीर्घ दीर्घ)mem_err->responder_id);
	अगर (p > pvt->other_detail)
		*(p - 1) = '\0';

	edac_raw_mc_handle_error(e);

unlock:
	spin_unlock_irqrestore(&ghes_lock, flags);
पूर्ण

/*
 * Known प्रणालीs that are safe to enable this module.
 */
अटल काष्ठा acpi_platक्रमm_list plat_list[] = अणु
	अणु"HPE   ", "Server  ", 0, ACPI_SIG_FADT, all_versionsपूर्ण,
	अणु पूर्ण /* End */
पूर्ण;

पूर्णांक ghes_edac_रेजिस्टर(काष्ठा ghes *ghes, काष्ठा device *dev)
अणु
	bool fake = false;
	काष्ठा mem_ctl_info *mci;
	काष्ठा ghes_pvt *pvt;
	काष्ठा edac_mc_layer layers[1];
	अचिन्हित दीर्घ flags;
	पूर्णांक idx = -1;
	पूर्णांक rc = 0;

	अगर (IS_ENABLED(CONFIG_X86)) अणु
		/* Check अगर safe to enable on this प्रणाली */
		idx = acpi_match_platक्रमm_list(plat_list);
		अगर (!क्रमce_load && idx < 0)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		क्रमce_load = true;
		idx = 0;
	पूर्ण

	/* finish another registration/unregistration instance first */
	mutex_lock(&ghes_reg_mutex);

	/*
	 * We have only one logical memory controller to which all DIMMs beदीर्घ.
	 */
	अगर (refcount_inc_not_zero(&ghes_refcount))
		जाओ unlock;

	ghes_scan_प्रणाली();

	/* Check अगर we've got a bogus BIOS */
	अगर (!ghes_hw.num_dimms) अणु
		fake = true;
		ghes_hw.num_dimms = 1;
	पूर्ण

	layers[0].type = EDAC_MC_LAYER_ALL_MEM;
	layers[0].size = ghes_hw.num_dimms;
	layers[0].is_virt_csrow = true;

	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(काष्ठा ghes_pvt));
	अगर (!mci) अणु
		pr_info("Can't allocate memory for EDAC data\n");
		rc = -ENOMEM;
		जाओ unlock;
	पूर्ण

	pvt		= mci->pvt_info;
	pvt->mci	= mci;

	mci->pdev = dev;
	mci->mtype_cap = MEM_FLAG_EMPTY;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = "ghes_edac.c";
	mci->ctl_name = "ghes_edac";
	mci->dev_name = "ghes";

	अगर (fake) अणु
		pr_info("This system has a very crappy BIOS: It doesn't even list the DIMMS.\n");
		pr_info("Its SMBIOS info is wrong. It is doubtful that the error report would\n");
		pr_info("work on such system. Use this driver with caution\n");
	पूर्ण अन्यथा अगर (idx < 0) अणु
		pr_info("This EDAC driver relies on BIOS to enumerate memory and get error reports.\n");
		pr_info("Unfortunately, not all BIOSes reflect the memory layout correctly.\n");
		pr_info("So, the end result of using this driver varies from vendor to vendor.\n");
		pr_info("If you find incorrect reports, please contact your hardware vendor\n");
		pr_info("to correct its BIOS.\n");
		pr_info("This system has %d DIMM sockets.\n", ghes_hw.num_dimms);
	पूर्ण

	अगर (!fake) अणु
		काष्ठा dimm_info *src, *dst;
		पूर्णांक i = 0;

		mci_क्रम_each_dimm(mci, dst) अणु
			src = &ghes_hw.dimms[i];

			dst->idx	   = src->idx;
			dst->smbios_handle = src->smbios_handle;
			dst->nr_pages	   = src->nr_pages;
			dst->mtype	   = src->mtype;
			dst->edac_mode	   = src->edac_mode;
			dst->dtype	   = src->dtype;
			dst->grain	   = src->grain;

			/*
			 * If no src->label, preserve शेष label asचिन्हित
			 * from EDAC core.
			 */
			अगर (म_माप(src->label))
				स_नकल(dst->label, src->label, माप(src->label));

			i++;
		पूर्ण

	पूर्ण अन्यथा अणु
		काष्ठा dimm_info *dimm = edac_get_dimm(mci, 0, 0, 0);

		dimm->nr_pages = 1;
		dimm->grain = 128;
		dimm->mtype = MEM_UNKNOWN;
		dimm->dtype = DEV_UNKNOWN;
		dimm->edac_mode = EDAC_SECDED;
	पूर्ण

	rc = edac_mc_add_mc(mci);
	अगर (rc < 0) अणु
		pr_info("Can't register with the EDAC core\n");
		edac_mc_मुक्त(mci);
		rc = -ENODEV;
		जाओ unlock;
	पूर्ण

	spin_lock_irqsave(&ghes_lock, flags);
	ghes_pvt = pvt;
	spin_unlock_irqrestore(&ghes_lock, flags);

	/* only set on success */
	refcount_set(&ghes_refcount, 1);

unlock:

	/* Not needed anymore */
	kमुक्त(ghes_hw.dimms);
	ghes_hw.dimms = शून्य;

	mutex_unlock(&ghes_reg_mutex);

	वापस rc;
पूर्ण

व्योम ghes_edac_unरेजिस्टर(काष्ठा ghes *ghes)
अणु
	काष्ठा mem_ctl_info *mci;
	अचिन्हित दीर्घ flags;

	अगर (!क्रमce_load)
		वापस;

	mutex_lock(&ghes_reg_mutex);

	प्रणाली_scanned = false;
	स_रखो(&ghes_hw, 0, माप(काष्ठा ghes_hw_desc));

	अगर (!refcount_dec_and_test(&ghes_refcount))
		जाओ unlock;

	/*
	 * Wait क्रम the irq handler being finished.
	 */
	spin_lock_irqsave(&ghes_lock, flags);
	mci = ghes_pvt ? ghes_pvt->mci : शून्य;
	ghes_pvt = शून्य;
	spin_unlock_irqrestore(&ghes_lock, flags);

	अगर (!mci)
		जाओ unlock;

	mci = edac_mc_del_mc(mci->pdev);
	अगर (mci)
		edac_mc_मुक्त(mci);

unlock:
	mutex_unlock(&ghes_reg_mutex);
पूर्ण
