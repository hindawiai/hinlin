<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UEFI Common Platक्रमm Error Record (CPER) support
 *
 * Copyright (C) 2010, Intel Corp.
 *	Author: Huang Ying <ying.huang@पूर्णांकel.com>
 *
 * CPER is the क्रमmat used to describe platक्रमm hardware error by
 * various tables, such as ERST, BERT and HEST etc.
 *
 * For more inक्रमmation about CPER, please refer to Appendix N of UEFI
 * Specअगरication version 2.4.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/cper.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/bcd.h>
#समावेश <acpi/ghes.h>
#समावेश <ras/ras_event.h>

अटल अक्षर rcd_decode_str[CPER_REC_LEN];

/*
 * CPER record ID need to be unique even after reboot, because record
 * ID is used as index क्रम ERST storage, जबतक CPER records from
 * multiple boot may co-exist in ERST.
 */
u64 cper_next_record_id(व्योम)
अणु
	अटल atomic64_t seq;

	अगर (!atomic64_पढ़ो(&seq)) अणु
		समय64_t समय = kसमय_get_real_seconds();

		/*
		 * This code is unlikely to still be needed in year 2106,
		 * but just in हाल, let's use a few more bits क्रम बारtamps
		 * after y2038 to be sure they keep increasing monotonically
		 * क्रम the next few hundred years...
		 */
		अगर (समय < 0x80000000)
			atomic64_set(&seq, (kसमय_get_real_seconds()) << 32);
		अन्यथा
			atomic64_set(&seq, 0x8000000000000000ull |
					   kसमय_get_real_seconds() << 24);
	पूर्ण

	वापस atomic64_inc_वापस(&seq);
पूर्ण
EXPORT_SYMBOL_GPL(cper_next_record_id);

अटल स्थिर अक्षर * स्थिर severity_strs[] = अणु
	"recoverable",
	"fatal",
	"corrected",
	"info",
पूर्ण;

स्थिर अक्षर *cper_severity_str(अचिन्हित पूर्णांक severity)
अणु
	वापस severity < ARRAY_SIZE(severity_strs) ?
		severity_strs[severity] : "unknown";
पूर्ण
EXPORT_SYMBOL_GPL(cper_severity_str);

/*
 * cper_prपूर्णांक_bits - prपूर्णांक strings क्रम set bits
 * @pfx: prefix क्रम each line, including log level and prefix string
 * @bits: bit mask
 * @strs: string array, indexed by bit position
 * @strs_size: size of the string array: @strs
 *
 * For each set bit in @bits, prपूर्णांक the corresponding string in @strs.
 * If the output length is दीर्घer than 80, multiple line will be
 * prपूर्णांकed, with @pfx is prपूर्णांकed at the beginning of each line.
 */
व्योम cper_prपूर्णांक_bits(स्थिर अक्षर *pfx, अचिन्हित पूर्णांक bits,
		     स्थिर अक्षर * स्थिर strs[], अचिन्हित पूर्णांक strs_size)
अणु
	पूर्णांक i, len = 0;
	स्थिर अक्षर *str;
	अक्षर buf[84];

	क्रम (i = 0; i < strs_size; i++) अणु
		अगर (!(bits & (1U << i)))
			जारी;
		str = strs[i];
		अगर (!str)
			जारी;
		अगर (len && len + म_माप(str) + 2 > 80) अणु
			prपूर्णांकk("%s\n", buf);
			len = 0;
		पूर्ण
		अगर (!len)
			len = snम_लिखो(buf, माप(buf), "%s%s", pfx, str);
		अन्यथा
			len += scnम_लिखो(buf+len, माप(buf)-len, ", %s", str);
	पूर्ण
	अगर (len)
		prपूर्णांकk("%s\n", buf);
पूर्ण

अटल स्थिर अक्षर * स्थिर proc_type_strs[] = अणु
	"IA32/X64",
	"IA64",
	"ARM",
पूर्ण;

अटल स्थिर अक्षर * स्थिर proc_isa_strs[] = अणु
	"IA32",
	"IA64",
	"X64",
	"ARM A32/T32",
	"ARM A64",
पूर्ण;

स्थिर अक्षर * स्थिर cper_proc_error_type_strs[] = अणु
	"cache error",
	"TLB error",
	"bus error",
	"micro-architectural error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर proc_op_strs[] = अणु
	"unknown or generic",
	"data read",
	"data write",
	"instruction execution",
पूर्ण;

अटल स्थिर अक्षर * स्थिर proc_flag_strs[] = अणु
	"restartable",
	"precise IP",
	"overflow",
	"corrected",
पूर्ण;

अटल व्योम cper_prपूर्णांक_proc_generic(स्थिर अक्षर *pfx,
				    स्थिर काष्ठा cper_sec_proc_generic *proc)
अणु
	अगर (proc->validation_bits & CPER_PROC_VALID_TYPE)
		prपूर्णांकk("%s""processor_type: %d, %s\n", pfx, proc->proc_type,
		       proc->proc_type < ARRAY_SIZE(proc_type_strs) ?
		       proc_type_strs[proc->proc_type] : "unknown");
	अगर (proc->validation_bits & CPER_PROC_VALID_ISA)
		prपूर्णांकk("%s""processor_isa: %d, %s\n", pfx, proc->proc_isa,
		       proc->proc_isa < ARRAY_SIZE(proc_isa_strs) ?
		       proc_isa_strs[proc->proc_isa] : "unknown");
	अगर (proc->validation_bits & CPER_PROC_VALID_ERROR_TYPE) अणु
		prपूर्णांकk("%s""error_type: 0x%02x\n", pfx, proc->proc_error_type);
		cper_prपूर्णांक_bits(pfx, proc->proc_error_type,
				cper_proc_error_type_strs,
				ARRAY_SIZE(cper_proc_error_type_strs));
	पूर्ण
	अगर (proc->validation_bits & CPER_PROC_VALID_OPERATION)
		prपूर्णांकk("%s""operation: %d, %s\n", pfx, proc->operation,
		       proc->operation < ARRAY_SIZE(proc_op_strs) ?
		       proc_op_strs[proc->operation] : "unknown");
	अगर (proc->validation_bits & CPER_PROC_VALID_FLAGS) अणु
		prपूर्णांकk("%s""flags: 0x%02x\n", pfx, proc->flags);
		cper_prपूर्णांक_bits(pfx, proc->flags, proc_flag_strs,
				ARRAY_SIZE(proc_flag_strs));
	पूर्ण
	अगर (proc->validation_bits & CPER_PROC_VALID_LEVEL)
		prपूर्णांकk("%s""level: %d\n", pfx, proc->level);
	अगर (proc->validation_bits & CPER_PROC_VALID_VERSION)
		prपूर्णांकk("%s""version_info: 0x%016llx\n", pfx, proc->cpu_version);
	अगर (proc->validation_bits & CPER_PROC_VALID_ID)
		prपूर्णांकk("%s""processor_id: 0x%016llx\n", pfx, proc->proc_id);
	अगर (proc->validation_bits & CPER_PROC_VALID_TARGET_ADDRESS)
		prपूर्णांकk("%s""target_address: 0x%016llx\n",
		       pfx, proc->target_addr);
	अगर (proc->validation_bits & CPER_PROC_VALID_REQUESTOR_ID)
		prपूर्णांकk("%s""requestor_id: 0x%016llx\n",
		       pfx, proc->requestor_id);
	अगर (proc->validation_bits & CPER_PROC_VALID_RESPONDER_ID)
		prपूर्णांकk("%s""responder_id: 0x%016llx\n",
		       pfx, proc->responder_id);
	अगर (proc->validation_bits & CPER_PROC_VALID_IP)
		prपूर्णांकk("%s""IP: 0x%016llx\n", pfx, proc->ip);
पूर्ण

अटल स्थिर अक्षर * स्थिर mem_err_type_strs[] = अणु
	"unknown",
	"no error",
	"single-bit ECC",
	"multi-bit ECC",
	"single-symbol chipkill ECC",
	"multi-symbol chipkill ECC",
	"master abort",
	"target abort",
	"parity error",
	"watchdog timeout",
	"invalid address",
	"mirror Broken",
	"memory sparing",
	"scrub corrected error",
	"scrub uncorrected error",
	"physical memory map-out event",
पूर्ण;

स्थिर अक्षर *cper_mem_err_type_str(अचिन्हित पूर्णांक etype)
अणु
	वापस etype < ARRAY_SIZE(mem_err_type_strs) ?
		mem_err_type_strs[etype] : "unknown";
पूर्ण
EXPORT_SYMBOL_GPL(cper_mem_err_type_str);

अटल पूर्णांक cper_mem_err_location(काष्ठा cper_mem_err_compact *mem, अक्षर *msg)
अणु
	u32 len, n;

	अगर (!msg)
		वापस 0;

	n = 0;
	len = CPER_REC_LEN - 1;
	अगर (mem->validation_bits & CPER_MEM_VALID_NODE)
		n += scnम_लिखो(msg + n, len - n, "node: %d ", mem->node);
	अगर (mem->validation_bits & CPER_MEM_VALID_CARD)
		n += scnम_लिखो(msg + n, len - n, "card: %d ", mem->card);
	अगर (mem->validation_bits & CPER_MEM_VALID_MODULE)
		n += scnम_लिखो(msg + n, len - n, "module: %d ", mem->module);
	अगर (mem->validation_bits & CPER_MEM_VALID_RANK_NUMBER)
		n += scnम_लिखो(msg + n, len - n, "rank: %d ", mem->rank);
	अगर (mem->validation_bits & CPER_MEM_VALID_BANK)
		n += scnम_लिखो(msg + n, len - n, "bank: %d ", mem->bank);
	अगर (mem->validation_bits & CPER_MEM_VALID_BANK_GROUP)
		n += scnम_लिखो(msg + n, len - n, "bank_group: %d ",
			       mem->bank >> CPER_MEM_BANK_GROUP_SHIFT);
	अगर (mem->validation_bits & CPER_MEM_VALID_BANK_ADDRESS)
		n += scnम_लिखो(msg + n, len - n, "bank_address: %d ",
			       mem->bank & CPER_MEM_BANK_ADDRESS_MASK);
	अगर (mem->validation_bits & CPER_MEM_VALID_DEVICE)
		n += scnम_लिखो(msg + n, len - n, "device: %d ", mem->device);
	अगर (mem->validation_bits & (CPER_MEM_VALID_ROW | CPER_MEM_VALID_ROW_EXT)) अणु
		u32 row = mem->row;

		row |= cper_get_mem_extension(mem->validation_bits, mem->extended);
		n += scnम_लिखो(msg + n, len - n, "row: %d ", row);
	पूर्ण
	अगर (mem->validation_bits & CPER_MEM_VALID_COLUMN)
		n += scnम_लिखो(msg + n, len - n, "column: %d ", mem->column);
	अगर (mem->validation_bits & CPER_MEM_VALID_BIT_POSITION)
		n += scnम_लिखो(msg + n, len - n, "bit_position: %d ",
			       mem->bit_pos);
	अगर (mem->validation_bits & CPER_MEM_VALID_REQUESTOR_ID)
		n += scnम_लिखो(msg + n, len - n, "requestor_id: 0x%016llx ",
			       mem->requestor_id);
	अगर (mem->validation_bits & CPER_MEM_VALID_RESPONDER_ID)
		n += scnम_लिखो(msg + n, len - n, "responder_id: 0x%016llx ",
			       mem->responder_id);
	अगर (mem->validation_bits & CPER_MEM_VALID_TARGET_ID)
		scnम_लिखो(msg + n, len - n, "target_id: 0x%016llx ",
			  mem->target_id);
	अगर (mem->validation_bits & CPER_MEM_VALID_CHIP_ID)
		scnम_लिखो(msg + n, len - n, "chip_id: %d ",
			  mem->extended >> CPER_MEM_CHIP_ID_SHIFT);

	msg[n] = '\0';
	वापस n;
पूर्ण

अटल पूर्णांक cper_dimm_err_location(काष्ठा cper_mem_err_compact *mem, अक्षर *msg)
अणु
	u32 len, n;
	स्थिर अक्षर *bank = शून्य, *device = शून्य;

	अगर (!msg || !(mem->validation_bits & CPER_MEM_VALID_MODULE_HANDLE))
		वापस 0;

	len = CPER_REC_LEN;
	dmi_memdev_name(mem->mem_dev_handle, &bank, &device);
	अगर (bank && device)
		n = snम_लिखो(msg, len, "DIMM location: %s %s ", bank, device);
	अन्यथा
		n = snम_लिखो(msg, len,
			     "DIMM location: not present. DMI handle: 0x%.4x ",
			     mem->mem_dev_handle);

	वापस n;
पूर्ण

व्योम cper_mem_err_pack(स्थिर काष्ठा cper_sec_mem_err *mem,
		       काष्ठा cper_mem_err_compact *cmem)
अणु
	cmem->validation_bits = mem->validation_bits;
	cmem->node = mem->node;
	cmem->card = mem->card;
	cmem->module = mem->module;
	cmem->bank = mem->bank;
	cmem->device = mem->device;
	cmem->row = mem->row;
	cmem->column = mem->column;
	cmem->bit_pos = mem->bit_pos;
	cmem->requestor_id = mem->requestor_id;
	cmem->responder_id = mem->responder_id;
	cmem->target_id = mem->target_id;
	cmem->extended = mem->extended;
	cmem->rank = mem->rank;
	cmem->mem_array_handle = mem->mem_array_handle;
	cmem->mem_dev_handle = mem->mem_dev_handle;
पूर्ण

स्थिर अक्षर *cper_mem_err_unpack(काष्ठा trace_seq *p,
				काष्ठा cper_mem_err_compact *cmem)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	अगर (cper_mem_err_location(cmem, rcd_decode_str))
		trace_seq_म_लिखो(p, "%s", rcd_decode_str);
	अगर (cper_dimm_err_location(cmem, rcd_decode_str))
		trace_seq_म_लिखो(p, "%s", rcd_decode_str);
	trace_seq_अ_दो(p, '\0');

	वापस ret;
पूर्ण

अटल व्योम cper_prपूर्णांक_mem(स्थिर अक्षर *pfx, स्थिर काष्ठा cper_sec_mem_err *mem,
	पूर्णांक len)
अणु
	काष्ठा cper_mem_err_compact cmem;

	/* Don't trust UEFI 2.1/2.2 काष्ठाure with bad validation bits */
	अगर (len == माप(काष्ठा cper_sec_mem_err_old) &&
	    (mem->validation_bits & ~(CPER_MEM_VALID_RANK_NUMBER - 1))) अणु
		pr_err(FW_WARN "valid bits set for fields beyond structure\n");
		वापस;
	पूर्ण
	अगर (mem->validation_bits & CPER_MEM_VALID_ERROR_STATUS)
		prपूर्णांकk("%s""error_status: 0x%016llx\n", pfx, mem->error_status);
	अगर (mem->validation_bits & CPER_MEM_VALID_PA)
		prपूर्णांकk("%s""physical_address: 0x%016llx\n",
		       pfx, mem->physical_addr);
	अगर (mem->validation_bits & CPER_MEM_VALID_PA_MASK)
		prपूर्णांकk("%s""physical_address_mask: 0x%016llx\n",
		       pfx, mem->physical_addr_mask);
	cper_mem_err_pack(mem, &cmem);
	अगर (cper_mem_err_location(&cmem, rcd_decode_str))
		prपूर्णांकk("%s%s\n", pfx, rcd_decode_str);
	अगर (mem->validation_bits & CPER_MEM_VALID_ERROR_TYPE) अणु
		u8 etype = mem->error_type;
		prपूर्णांकk("%s""error_type: %d, %s\n", pfx, etype,
		       cper_mem_err_type_str(etype));
	पूर्ण
	अगर (cper_dimm_err_location(&cmem, rcd_decode_str))
		prपूर्णांकk("%s%s\n", pfx, rcd_decode_str);
पूर्ण

अटल स्थिर अक्षर * स्थिर pcie_port_type_strs[] = अणु
	"PCIe end point",
	"legacy PCI end point",
	"unknown",
	"unknown",
	"root port",
	"upstream switch port",
	"downstream switch port",
	"PCIe to PCI/PCI-X bridge",
	"PCI/PCI-X to PCIe bridge",
	"root complex integrated endpoint device",
	"root complex event collector",
पूर्ण;

अटल व्योम cper_prपूर्णांक_pcie(स्थिर अक्षर *pfx, स्थिर काष्ठा cper_sec_pcie *pcie,
			    स्थिर काष्ठा acpi_hest_generic_data *gdata)
अणु
	अगर (pcie->validation_bits & CPER_PCIE_VALID_PORT_TYPE)
		prपूर्णांकk("%s""port_type: %d, %s\n", pfx, pcie->port_type,
		       pcie->port_type < ARRAY_SIZE(pcie_port_type_strs) ?
		       pcie_port_type_strs[pcie->port_type] : "unknown");
	अगर (pcie->validation_bits & CPER_PCIE_VALID_VERSION)
		prपूर्णांकk("%s""version: %d.%d\n", pfx,
		       pcie->version.major, pcie->version.minor);
	अगर (pcie->validation_bits & CPER_PCIE_VALID_COMMAND_STATUS)
		prपूर्णांकk("%s""command: 0x%04x, status: 0x%04x\n", pfx,
		       pcie->command, pcie->status);
	अगर (pcie->validation_bits & CPER_PCIE_VALID_DEVICE_ID) अणु
		स्थिर __u8 *p;
		prपूर्णांकk("%s""device_id: %04x:%02x:%02x.%x\n", pfx,
		       pcie->device_id.segment, pcie->device_id.bus,
		       pcie->device_id.device, pcie->device_id.function);
		prपूर्णांकk("%s""slot: %d\n", pfx,
		       pcie->device_id.slot >> CPER_PCIE_SLOT_SHIFT);
		prपूर्णांकk("%s""secondary_bus: 0x%02x\n", pfx,
		       pcie->device_id.secondary_bus);
		prपूर्णांकk("%s""vendor_id: 0x%04x, device_id: 0x%04x\n", pfx,
		       pcie->device_id.venकरोr_id, pcie->device_id.device_id);
		p = pcie->device_id.class_code;
		prपूर्णांकk("%s""class_code: %02x%02x%02x\n", pfx, p[2], p[1], p[0]);
	पूर्ण
	अगर (pcie->validation_bits & CPER_PCIE_VALID_SERIAL_NUMBER)
		prपूर्णांकk("%s""serial number: 0x%04x, 0x%04x\n", pfx,
		       pcie->serial_number.lower, pcie->serial_number.upper);
	अगर (pcie->validation_bits & CPER_PCIE_VALID_BRIDGE_CONTROL_STATUS)
		prपूर्णांकk(
	"%s""bridge: secondary_status: 0x%04x, control: 0x%04x\n",
	pfx, pcie->bridge.secondary_status, pcie->bridge.control);

	/* Fatal errors call __ghes_panic() beक्रमe AER handler prपूर्णांकs this */
	अगर ((pcie->validation_bits & CPER_PCIE_VALID_AER_INFO) &&
	    (gdata->error_severity & CPER_SEV_FATAL)) अणु
		काष्ठा aer_capability_regs *aer;

		aer = (काष्ठा aer_capability_regs *)pcie->aer_info;
		prपूर्णांकk("%saer_uncor_status: 0x%08x, aer_uncor_mask: 0x%08x\n",
		       pfx, aer->uncor_status, aer->uncor_mask);
		prपूर्णांकk("%saer_uncor_severity: 0x%08x\n",
		       pfx, aer->uncor_severity);
		prपूर्णांकk("%sTLP Header: %08x %08x %08x %08x\n", pfx,
		       aer->header_log.dw0, aer->header_log.dw1,
		       aer->header_log.dw2, aer->header_log.dw3);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर fw_err_rec_type_strs[] = अणु
	"IPF SAL Error Record",
	"SOC Firmware Error Record Type1 (Legacy CrashLog Support)",
	"SOC Firmware Error Record Type2",
पूर्ण;

अटल व्योम cper_prपूर्णांक_fw_err(स्थिर अक्षर *pfx,
			      काष्ठा acpi_hest_generic_data *gdata,
			      स्थिर काष्ठा cper_sec_fw_err_rec_ref *fw_err)
अणु
	व्योम *buf = acpi_hest_get_payload(gdata);
	u32 offset, length = gdata->error_data_length;

	prपूर्णांकk("%s""Firmware Error Record Type: %s\n", pfx,
	       fw_err->record_type < ARRAY_SIZE(fw_err_rec_type_strs) ?
	       fw_err_rec_type_strs[fw_err->record_type] : "unknown");
	prपूर्णांकk("%s""Revision: %d\n", pfx, fw_err->revision);

	/* Record Type based on UEFI 2.7 */
	अगर (fw_err->revision == 0) अणु
		prपूर्णांकk("%s""Record Identifier: %08llx\n", pfx,
		       fw_err->record_identअगरier);
	पूर्ण अन्यथा अगर (fw_err->revision == 2) अणु
		prपूर्णांकk("%s""Record Identifier: %pUl\n", pfx,
		       &fw_err->record_identअगरier_guid);
	पूर्ण

	/*
	 * The FW error record may contain trailing data beyond the
	 * काष्ठाure defined by the specअगरication. As the fields
	 * defined (and hence the offset of any trailing data) vary
	 * with the revision, set the offset to account क्रम this
	 * variation.
	 */
	अगर (fw_err->revision == 0) अणु
		/* record_identअगरier_guid not defined */
		offset = दुरत्व(काष्ठा cper_sec_fw_err_rec_ref,
				  record_identअगरier_guid);
	पूर्ण अन्यथा अगर (fw_err->revision == 1) अणु
		/* record_identअगरier not defined */
		offset = दुरत्व(काष्ठा cper_sec_fw_err_rec_ref,
				  record_identअगरier);
	पूर्ण अन्यथा अणु
		offset = माप(*fw_err);
	पूर्ण

	buf += offset;
	length -= offset;

	prपूर्णांक_hex_dump(pfx, "", DUMP_PREFIX_OFFSET, 16, 4, buf, length, true);
पूर्ण

अटल व्योम cper_prपूर्णांक_tstamp(स्थिर अक्षर *pfx,
				   काष्ठा acpi_hest_generic_data_v300 *gdata)
अणु
	__u8 hour, min, sec, day, mon, year, century, *बारtamp;

	अगर (gdata->validation_bits & ACPI_HEST_GEN_VALID_TIMESTAMP) अणु
		बारtamp = (__u8 *)&(gdata->समय_stamp);
		sec       = bcd2bin(बारtamp[0]);
		min       = bcd2bin(बारtamp[1]);
		hour      = bcd2bin(बारtamp[2]);
		day       = bcd2bin(बारtamp[4]);
		mon       = bcd2bin(बारtamp[5]);
		year      = bcd2bin(बारtamp[6]);
		century   = bcd2bin(बारtamp[7]);

		prपूर्णांकk("%s%ststamp: %02d%02d-%02d-%02d %02d:%02d:%02d\n", pfx,
		       (बारtamp[3] & 0x1 ? "precise " : "imprecise "),
		       century, year, mon, day, hour, min, sec);
	पूर्ण
पूर्ण

अटल व्योम
cper_estatus_prपूर्णांक_section(स्थिर अक्षर *pfx, काष्ठा acpi_hest_generic_data *gdata,
			   पूर्णांक sec_no)
अणु
	guid_t *sec_type = (guid_t *)gdata->section_type;
	__u16 severity;
	अक्षर newpfx[64];

	अगर (acpi_hest_get_version(gdata) >= 3)
		cper_prपूर्णांक_tstamp(pfx, (काष्ठा acpi_hest_generic_data_v300 *)gdata);

	severity = gdata->error_severity;
	prपूर्णांकk("%s""Error %d, type: %s\n", pfx, sec_no,
	       cper_severity_str(severity));
	अगर (gdata->validation_bits & CPER_SEC_VALID_FRU_ID)
		prपूर्णांकk("%s""fru_id: %pUl\n", pfx, gdata->fru_id);
	अगर (gdata->validation_bits & CPER_SEC_VALID_FRU_TEXT)
		prपूर्णांकk("%s""fru_text: %.20s\n", pfx, gdata->fru_text);

	snम_लिखो(newpfx, माप(newpfx), "%s ", pfx);
	अगर (guid_equal(sec_type, &CPER_SEC_PROC_GENERIC)) अणु
		काष्ठा cper_sec_proc_generic *proc_err = acpi_hest_get_payload(gdata);

		prपूर्णांकk("%s""section_type: general processor error\n", newpfx);
		अगर (gdata->error_data_length >= माप(*proc_err))
			cper_prपूर्णांक_proc_generic(newpfx, proc_err);
		अन्यथा
			जाओ err_section_too_small;
	पूर्ण अन्यथा अगर (guid_equal(sec_type, &CPER_SEC_PLATFORM_MEM)) अणु
		काष्ठा cper_sec_mem_err *mem_err = acpi_hest_get_payload(gdata);

		prपूर्णांकk("%s""section_type: memory error\n", newpfx);
		अगर (gdata->error_data_length >=
		    माप(काष्ठा cper_sec_mem_err_old))
			cper_prपूर्णांक_mem(newpfx, mem_err,
				       gdata->error_data_length);
		अन्यथा
			जाओ err_section_too_small;
	पूर्ण अन्यथा अगर (guid_equal(sec_type, &CPER_SEC_PCIE)) अणु
		काष्ठा cper_sec_pcie *pcie = acpi_hest_get_payload(gdata);

		prपूर्णांकk("%s""section_type: PCIe error\n", newpfx);
		अगर (gdata->error_data_length >= माप(*pcie))
			cper_prपूर्णांक_pcie(newpfx, pcie, gdata);
		अन्यथा
			जाओ err_section_too_small;
#अगर defined(CONFIG_ARM64) || defined(CONFIG_ARM)
	पूर्ण अन्यथा अगर (guid_equal(sec_type, &CPER_SEC_PROC_ARM)) अणु
		काष्ठा cper_sec_proc_arm *arm_err = acpi_hest_get_payload(gdata);

		prपूर्णांकk("%ssection_type: ARM processor error\n", newpfx);
		अगर (gdata->error_data_length >= माप(*arm_err))
			cper_prपूर्णांक_proc_arm(newpfx, arm_err);
		अन्यथा
			जाओ err_section_too_small;
#पूर्ण_अगर
#अगर defined(CONFIG_UEFI_CPER_X86)
	पूर्ण अन्यथा अगर (guid_equal(sec_type, &CPER_SEC_PROC_IA)) अणु
		काष्ठा cper_sec_proc_ia *ia_err = acpi_hest_get_payload(gdata);

		prपूर्णांकk("%ssection_type: IA32/X64 processor error\n", newpfx);
		अगर (gdata->error_data_length >= माप(*ia_err))
			cper_prपूर्णांक_proc_ia(newpfx, ia_err);
		अन्यथा
			जाओ err_section_too_small;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (guid_equal(sec_type, &CPER_SEC_FW_ERR_REC_REF)) अणु
		काष्ठा cper_sec_fw_err_rec_ref *fw_err = acpi_hest_get_payload(gdata);

		prपूर्णांकk("%ssection_type: Firmware Error Record Reference\n",
		       newpfx);
		/* The minimal FW Error Record contains 16 bytes */
		अगर (gdata->error_data_length >= SZ_16)
			cper_prपूर्णांक_fw_err(newpfx, gdata, fw_err);
		अन्यथा
			जाओ err_section_too_small;
	पूर्ण अन्यथा अणु
		स्थिर व्योम *err = acpi_hest_get_payload(gdata);

		prपूर्णांकk("%ssection type: unknown, %pUl\n", newpfx, sec_type);
		prपूर्णांकk("%ssection length: %#x\n", newpfx,
		       gdata->error_data_length);
		prपूर्णांक_hex_dump(newpfx, "", DUMP_PREFIX_OFFSET, 16, 4, err,
			       gdata->error_data_length, true);
	पूर्ण

	वापस;

err_section_too_small:
	pr_err(FW_WARN "error section length is too small\n");
पूर्ण

व्योम cper_estatus_prपूर्णांक(स्थिर अक्षर *pfx,
			स्थिर काष्ठा acpi_hest_generic_status *estatus)
अणु
	काष्ठा acpi_hest_generic_data *gdata;
	पूर्णांक sec_no = 0;
	अक्षर newpfx[64];
	__u16 severity;

	severity = estatus->error_severity;
	अगर (severity == CPER_SEV_CORRECTED)
		prपूर्णांकk("%s%s\n", pfx,
		       "It has been corrected by h/w "
		       "and requires no further action");
	prपूर्णांकk("%s""event severity: %s\n", pfx, cper_severity_str(severity));
	snम_लिखो(newpfx, माप(newpfx), "%s ", pfx);

	apei_estatus_क्रम_each_section(estatus, gdata) अणु
		cper_estatus_prपूर्णांक_section(newpfx, gdata, sec_no);
		sec_no++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cper_estatus_prपूर्णांक);

पूर्णांक cper_estatus_check_header(स्थिर काष्ठा acpi_hest_generic_status *estatus)
अणु
	अगर (estatus->data_length &&
	    estatus->data_length < माप(काष्ठा acpi_hest_generic_data))
		वापस -EINVAL;
	अगर (estatus->raw_data_length &&
	    estatus->raw_data_offset < माप(*estatus) + estatus->data_length)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cper_estatus_check_header);

पूर्णांक cper_estatus_check(स्थिर काष्ठा acpi_hest_generic_status *estatus)
अणु
	काष्ठा acpi_hest_generic_data *gdata;
	अचिन्हित पूर्णांक data_len, record_size;
	पूर्णांक rc;

	rc = cper_estatus_check_header(estatus);
	अगर (rc)
		वापस rc;

	data_len = estatus->data_length;

	apei_estatus_क्रम_each_section(estatus, gdata) अणु
		अगर (माप(काष्ठा acpi_hest_generic_data) > data_len)
			वापस -EINVAL;

		record_size = acpi_hest_get_record_size(gdata);
		अगर (record_size > data_len)
			वापस -EINVAL;

		data_len -= record_size;
	पूर्ण
	अगर (data_len)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cper_estatus_check);
