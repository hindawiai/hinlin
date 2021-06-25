<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/acpi.h>
#समावेश "i915_drv.h"
#समावेश "gvt.h"

/*
 * Note: Only क्रम GVT-g भव VBT generation, other usage must
 * not करो like this.
 */
#घोषणा _INTEL_BIOS_PRIVATE
#समावेश "display/intel_vbt_defs.h"

#घोषणा OPREGION_SIGNATURE "IntelGraphicsMem"
#घोषणा MBOX_VBT      (1<<3)

/* device handle */
#घोषणा DEVICE_TYPE_CRT    0x01
#घोषणा DEVICE_TYPE_EFP1   0x04
#घोषणा DEVICE_TYPE_EFP2   0x40
#घोषणा DEVICE_TYPE_EFP3   0x20
#घोषणा DEVICE_TYPE_EFP4   0x10

काष्ठा opregion_header अणु
	u8 signature[16];
	u32 size;
	u32 opregion_ver;
	u8 bios_ver[32];
	u8 vbios_ver[16];
	u8 driver_ver[16];
	u32 mboxes;
	u32 driver_model;
	u32 pcon;
	u8 dver[32];
	u8 rsvd[124];
पूर्ण __packed;

काष्ठा bdb_data_header अणु
	u8 id;
	u16 size; /* data size */
पूर्ण __packed;

/* For supporting winकरोws guest with opregion, here hardcode the emulated
 * bdb header version as '186', and the corresponding child_device_config
 * length should be '33' but not '38'.
 */
काष्ठा efp_child_device_config अणु
	u16 handle;
	u16 device_type;
	u16 device_class;
	u8 i2c_speed;
	u8 dp_onboard_redriver; /* 158 */
	u8 dp_onकरोck_redriver; /* 158 */
	u8 hdmi_level_shअगरter_value:4; /* 169 */
	u8 hdmi_max_data_rate:4; /* 204 */
	u16 dtd_buf_ptr; /* 161 */
	u8 edidless_efp:1; /* 161 */
	u8 compression_enable:1; /* 198 */
	u8 compression_method:1; /* 198 */
	u8 ganged_edp:1; /* 202 */
	u8 skip0:4;
	u8 compression_काष्ठाure_index:4; /* 198 */
	u8 skip1:4;
	u8 slave_port; /*  202 */
	u8 skip2;
	u8 dvo_port;
	u8 i2c_pin; /* क्रम add-in card */
	u8 slave_addr; /* क्रम add-in card */
	u8 ddc_pin;
	u16 edid_ptr;
	u8 dvo_config;
	u8 efp_करोcked_port:1; /* 158 */
	u8 lane_reversal:1; /* 184 */
	u8 onboard_lspcon:1; /* 192 */
	u8 iboost_enable:1; /* 196 */
	u8 hpd_invert:1; /* BXT 196 */
	u8 slip3:3;
	u8 hdmi_compat:1;
	u8 dp_compat:1;
	u8 पंचांगds_compat:1;
	u8 skip4:5;
	u8 aux_channel;
	u8 करोngle_detect;
	u8 pipe_cap:2;
	u8 sdvo_stall:1; /* 158 */
	u8 hpd_status:2;
	u8 पूर्णांकegrated_encoder:1;
	u8 skip5:2;
	u8 dvo_wiring;
	u8 mipi_bridge_type; /* 171 */
	u16 device_class_ext;
	u8 dvo_function;
पूर्ण __packed;

काष्ठा vbt अणु
	/* header->bdb_offset poपूर्णांक to bdb_header offset */
	काष्ठा vbt_header header;
	काष्ठा bdb_header bdb_header;

	काष्ठा bdb_data_header general_features_header;
	काष्ठा bdb_general_features general_features;

	काष्ठा bdb_data_header general_definitions_header;
	काष्ठा bdb_general_definitions general_definitions;

	काष्ठा efp_child_device_config child0;
	काष्ठा efp_child_device_config child1;
	काष्ठा efp_child_device_config child2;
	काष्ठा efp_child_device_config child3;

	काष्ठा bdb_data_header driver_features_header;
	काष्ठा bdb_driver_features driver_features;
पूर्ण;

अटल व्योम virt_vbt_generation(काष्ठा vbt *v)
अणु
	पूर्णांक num_child;

	स_रखो(v, 0, माप(काष्ठा vbt));

	v->header.signature[0] = '$';
	v->header.signature[1] = 'V';
	v->header.signature[2] = 'B';
	v->header.signature[3] = 'T';

	/* there's features depending on version! */
	v->header.version = 155;
	v->header.header_size = माप(v->header);
	v->header.vbt_size = माप(काष्ठा vbt);
	v->header.bdb_offset = दुरत्व(काष्ठा vbt, bdb_header);

	म_नकल(&v->bdb_header.signature[0], "BIOS_DATA_BLOCK");
	v->bdb_header.version = 186; /* child_dev_size = 33 */
	v->bdb_header.header_size = माप(v->bdb_header);

	v->bdb_header.bdb_size = माप(काष्ठा vbt) - माप(काष्ठा vbt_header);

	/* general features */
	v->general_features_header.id = BDB_GENERAL_FEATURES;
	v->general_features_header.size = माप(काष्ठा bdb_general_features);
	v->general_features.पूर्णांक_crt_support = 0;
	v->general_features.पूर्णांक_tv_support = 0;

	/* child device */
	num_child = 4; /* each port has one child */
	v->general_definitions.child_dev_size =
		माप(काष्ठा efp_child_device_config);
	v->general_definitions_header.id = BDB_GENERAL_DEFINITIONS;
	/* size will include child devices */
	v->general_definitions_header.size =
		माप(काष्ठा bdb_general_definitions) +
			num_child * v->general_definitions.child_dev_size;

	/* portA */
	v->child0.handle = DEVICE_TYPE_EFP1;
	v->child0.device_type = DEVICE_TYPE_DP;
	v->child0.dvo_port = DVO_PORT_DPA;
	v->child0.aux_channel = DP_AUX_A;
	v->child0.dp_compat = true;
	v->child0.पूर्णांकegrated_encoder = true;

	/* portB */
	v->child1.handle = DEVICE_TYPE_EFP2;
	v->child1.device_type = DEVICE_TYPE_DP;
	v->child1.dvo_port = DVO_PORT_DPB;
	v->child1.aux_channel = DP_AUX_B;
	v->child1.dp_compat = true;
	v->child1.पूर्णांकegrated_encoder = true;

	/* portC */
	v->child2.handle = DEVICE_TYPE_EFP3;
	v->child2.device_type = DEVICE_TYPE_DP;
	v->child2.dvo_port = DVO_PORT_DPC;
	v->child2.aux_channel = DP_AUX_C;
	v->child2.dp_compat = true;
	v->child2.पूर्णांकegrated_encoder = true;

	/* portD */
	v->child3.handle = DEVICE_TYPE_EFP4;
	v->child3.device_type = DEVICE_TYPE_DP;
	v->child3.dvo_port = DVO_PORT_DPD;
	v->child3.aux_channel = DP_AUX_D;
	v->child3.dp_compat = true;
	v->child3.पूर्णांकegrated_encoder = true;

	/* driver features */
	v->driver_features_header.id = BDB_DRIVER_FEATURES;
	v->driver_features_header.size = माप(काष्ठा bdb_driver_features);
	v->driver_features.lvds_config = BDB_DRIVER_FEATURE_NO_LVDS;
पूर्ण

/**
 * पूर्णांकel_vgpu_init_opregion - initialize the stuff used to emulate opregion
 * @vgpu: a vGPU
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_init_opregion(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	u8 *buf;
	काष्ठा opregion_header *header;
	काष्ठा vbt v;
	स्थिर अक्षर opregion_signature[16] = OPREGION_SIGNATURE;

	gvt_dbg_core("init vgpu%d opregion\n", vgpu->id);
	vgpu_opregion(vgpu)->va = (व्योम *)__get_मुक्त_pages(GFP_KERNEL |
			__GFP_ZERO,
			get_order(INTEL_GVT_OPREGION_SIZE));
	अगर (!vgpu_opregion(vgpu)->va) अणु
		gvt_err("fail to get memory for vgpu virt opregion\n");
		वापस -ENOMEM;
	पूर्ण

	/* emulated opregion with VBT mailbox only */
	buf = (u8 *)vgpu_opregion(vgpu)->va;
	header = (काष्ठा opregion_header *)buf;
	स_नकल(header->signature, opregion_signature,
	       माप(opregion_signature));
	header->size = 0x8;
	header->opregion_ver = 0x02000000;
	header->mboxes = MBOX_VBT;

	/* क्रम unknown reason, the value in LID field is incorrect
	 * which block the winकरोws guest, so workaround it by क्रमce
	 * setting it to "OPEN"
	 */
	buf[INTEL_GVT_OPREGION_CLID] = 0x3;

	/* emulated vbt from virt vbt generation */
	virt_vbt_generation(&v);
	स_नकल(buf + INTEL_GVT_OPREGION_VBT_OFFSET, &v, माप(काष्ठा vbt));

	वापस 0;
पूर्ण

अटल पूर्णांक map_vgpu_opregion(काष्ठा पूर्णांकel_vgpu *vgpu, bool map)
अणु
	u64 mfn;
	पूर्णांक i, ret;

	क्रम (i = 0; i < INTEL_GVT_OPREGION_PAGES; i++) अणु
		mfn = पूर्णांकel_gvt_hypervisor_virt_to_mfn(vgpu_opregion(vgpu)->va
			+ i * PAGE_SIZE);
		अगर (mfn == INTEL_GVT_INVALID_ADDR) अणु
			gvt_vgpu_err("fail to get MFN from VA\n");
			वापस -EINVAL;
		पूर्ण
		ret = पूर्णांकel_gvt_hypervisor_map_gfn_to_mfn(vgpu,
				vgpu_opregion(vgpu)->gfn[i],
				mfn, 1, map);
		अगर (ret) अणु
			gvt_vgpu_err("fail to map GFN to MFN, errno: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	vgpu_opregion(vgpu)->mapped = map;

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_opregion_base_ग_लिखो_handler - Opregion base रेजिस्टर ग_लिखो handler
 *
 * @vgpu: a vGPU
 * @gpa: guest physical address of opregion
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_opregion_base_ग_लिखो_handler(काष्ठा पूर्णांकel_vgpu *vgpu, u32 gpa)
अणु

	पूर्णांक i, ret = 0;

	gvt_dbg_core("emulate opregion from kernel\n");

	चयन (पूर्णांकel_gvt_host.hypervisor_type) अणु
	हाल INTEL_GVT_HYPERVISOR_KVM:
		क्रम (i = 0; i < INTEL_GVT_OPREGION_PAGES; i++)
			vgpu_opregion(vgpu)->gfn[i] = (gpa >> PAGE_SHIFT) + i;
		अवरोध;
	हाल INTEL_GVT_HYPERVISOR_XEN:
		/**
		 * Wins guest on Xengt will ग_लिखो this रेजिस्टर twice: xen
		 * hvmloader and winकरोws graphic driver.
		 */
		अगर (vgpu_opregion(vgpu)->mapped)
			map_vgpu_opregion(vgpu, false);

		क्रम (i = 0; i < INTEL_GVT_OPREGION_PAGES; i++)
			vgpu_opregion(vgpu)->gfn[i] = (gpa >> PAGE_SHIFT) + i;

		ret = map_vgpu_opregion(vgpu, true);
		अवरोध;
	शेष:
		ret = -EINVAL;
		gvt_vgpu_err("not supported hypervisor\n");
	पूर्ण

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_vgpu_clean_opregion - clean the stuff used to emulate opregion
 * @vgpu: a vGPU
 *
 */
व्योम पूर्णांकel_vgpu_clean_opregion(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	gvt_dbg_core("vgpu%d: clean vgpu opregion\n", vgpu->id);

	अगर (!vgpu_opregion(vgpu)->va)
		वापस;

	अगर (पूर्णांकel_gvt_host.hypervisor_type == INTEL_GVT_HYPERVISOR_XEN) अणु
		अगर (vgpu_opregion(vgpu)->mapped)
			map_vgpu_opregion(vgpu, false);
	पूर्ण अन्यथा अगर (पूर्णांकel_gvt_host.hypervisor_type == INTEL_GVT_HYPERVISOR_KVM) अणु
		/* Guest opregion is released by VFIO */
	पूर्ण
	मुक्त_pages((अचिन्हित दीर्घ)vgpu_opregion(vgpu)->va,
		   get_order(INTEL_GVT_OPREGION_SIZE));

	vgpu_opregion(vgpu)->va = शून्य;

पूर्ण


#घोषणा GVT_OPREGION_FUNC(scic)					\
	(अणु							\
	 u32 __ret;						\
	 __ret = (scic & OPREGION_SCIC_FUNC_MASK) >>		\
	 OPREGION_SCIC_FUNC_SHIFT;				\
	 __ret;							\
	 पूर्ण)

#घोषणा GVT_OPREGION_SUBFUNC(scic)				\
	(अणु							\
	 u32 __ret;						\
	 __ret = (scic & OPREGION_SCIC_SUBFUNC_MASK) >>		\
	 OPREGION_SCIC_SUBFUNC_SHIFT;				\
	 __ret;							\
	 पूर्ण)

अटल स्थिर अक्षर *opregion_func_name(u32 func)
अणु
	स्थिर अक्षर *name = शून्य;

	चयन (func) अणु
	हाल 0 ... 3:
	हाल 5:
	हाल 7 ... 15:
		name = "Reserved";
		अवरोध;

	हाल 4:
		name = "Get BIOS Data";
		अवरोध;

	हाल 6:
		name = "System BIOS Callbacks";
		अवरोध;

	शेष:
		name = "Unknown";
		अवरोध;
	पूर्ण
	वापस name;
पूर्ण

अटल स्थिर अक्षर *opregion_subfunc_name(u32 subfunc)
अणु
	स्थिर अक्षर *name = शून्य;

	चयन (subfunc) अणु
	हाल 0:
		name = "Supported Calls";
		अवरोध;

	हाल 1:
		name = "Requested Callbacks";
		अवरोध;

	हाल 2 ... 3:
	हाल 8 ... 9:
		name = "Reserved";
		अवरोध;

	हाल 5:
		name = "Boot Display";
		अवरोध;

	हाल 6:
		name = "TV-Standard/Video-Connector";
		अवरोध;

	हाल 7:
		name = "Internal Graphics";
		अवरोध;

	हाल 10:
		name = "Spread Spectrum Clocks";
		अवरोध;

	हाल 11:
		name = "Get AKSV";
		अवरोध;

	शेष:
		name = "Unknown";
		अवरोध;
	पूर्ण
	वापस name;
पूर्ण;

अटल bool querying_capabilities(u32 scic)
अणु
	u32 func, subfunc;

	func = GVT_OPREGION_FUNC(scic);
	subfunc = GVT_OPREGION_SUBFUNC(scic);

	अगर ((func == INTEL_GVT_OPREGION_SCIC_F_GETBIOSDATA &&
		subfunc == INTEL_GVT_OPREGION_SCIC_SF_SUPPRTEDCALLS)
		|| (func == INTEL_GVT_OPREGION_SCIC_F_GETBIOSDATA &&
		 subfunc == INTEL_GVT_OPREGION_SCIC_SF_REQEUSTEDCALLBACKS)
		|| (func == INTEL_GVT_OPREGION_SCIC_F_GETBIOSCALLBACKS &&
		 subfunc == INTEL_GVT_OPREGION_SCIC_SF_SUPPRTEDCALLS)) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * पूर्णांकel_vgpu_emulate_opregion_request - emulating OpRegion request
 * @vgpu: a vGPU
 * @swsci: SWSCI request
 *
 * Returns:
 * Zero on success, negative error code अगर failed
 */
पूर्णांक पूर्णांकel_vgpu_emulate_opregion_request(काष्ठा पूर्णांकel_vgpu *vgpu, u32 swsci)
अणु
	u32 scic, parm;
	u32 func, subfunc;
	u64 scic_pa = 0, parm_pa = 0;
	पूर्णांक ret;

	चयन (पूर्णांकel_gvt_host.hypervisor_type) अणु
	हाल INTEL_GVT_HYPERVISOR_XEN:
		scic = *((u32 *)vgpu_opregion(vgpu)->va +
					INTEL_GVT_OPREGION_SCIC);
		parm = *((u32 *)vgpu_opregion(vgpu)->va +
					INTEL_GVT_OPREGION_PARM);
		अवरोध;
	हाल INTEL_GVT_HYPERVISOR_KVM:
		scic_pa = (vgpu_opregion(vgpu)->gfn[0] << PAGE_SHIFT) +
					INTEL_GVT_OPREGION_SCIC;
		parm_pa = (vgpu_opregion(vgpu)->gfn[0] << PAGE_SHIFT) +
					INTEL_GVT_OPREGION_PARM;

		ret = पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, scic_pa,
						    &scic, माप(scic));
		अगर (ret) अणु
			gvt_vgpu_err("guest opregion read error %d, gpa 0x%llx, len %lu\n",
				ret, scic_pa, माप(scic));
			वापस ret;
		पूर्ण

		ret = पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, parm_pa,
						    &parm, माप(parm));
		अगर (ret) अणु
			gvt_vgpu_err("guest opregion read error %d, gpa 0x%llx, len %lu\n",
				ret, scic_pa, माप(scic));
			वापस ret;
		पूर्ण

		अवरोध;
	शेष:
		gvt_vgpu_err("not supported hypervisor\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(swsci & SWSCI_SCI_SELECT)) अणु
		gvt_vgpu_err("requesting SMI service\n");
		वापस 0;
	पूर्ण
	/* ignore non 0->1 trasitions */
	अगर ((vgpu_cfg_space(vgpu)[INTEL_GVT_PCI_SWSCI]
				& SWSCI_SCI_TRIGGER) ||
			!(swsci & SWSCI_SCI_TRIGGER)) अणु
		वापस 0;
	पूर्ण

	func = GVT_OPREGION_FUNC(scic);
	subfunc = GVT_OPREGION_SUBFUNC(scic);
	अगर (!querying_capabilities(scic)) अणु
		gvt_vgpu_err("requesting runtime service: func \"%s\","
				" subfunc \"%s\"\n",
				opregion_func_name(func),
				opregion_subfunc_name(subfunc));
		/*
		 * emulate निकास status of function call, '0' means
		 * "failure, generic, unsupported or unknown cause"
		 */
		scic &= ~OPREGION_SCIC_EXIT_MASK;
		जाओ out;
	पूर्ण

	scic = 0;
	parm = 0;

out:
	चयन (पूर्णांकel_gvt_host.hypervisor_type) अणु
	हाल INTEL_GVT_HYPERVISOR_XEN:
		*((u32 *)vgpu_opregion(vgpu)->va +
					INTEL_GVT_OPREGION_SCIC) = scic;
		*((u32 *)vgpu_opregion(vgpu)->va +
					INTEL_GVT_OPREGION_PARM) = parm;
		अवरोध;
	हाल INTEL_GVT_HYPERVISOR_KVM:
		ret = पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu, scic_pa,
						    &scic, माप(scic));
		अगर (ret) अणु
			gvt_vgpu_err("guest opregion write error %d, gpa 0x%llx, len %lu\n",
				ret, scic_pa, माप(scic));
			वापस ret;
		पूर्ण

		ret = पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu, parm_pa,
						    &parm, माप(parm));
		अगर (ret) अणु
			gvt_vgpu_err("guest opregion write error %d, gpa 0x%llx, len %lu\n",
				ret, scic_pa, माप(scic));
			वापस ret;
		पूर्ण

		अवरोध;
	शेष:
		gvt_vgpu_err("not supported hypervisor\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
