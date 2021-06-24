<शैली गुरु>
/*
 * Copyright(c) 2015 - 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/firmware.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>

#समावेश "hfi.h"
#समावेश "trace.h"

/*
 * Make it easy to toggle firmware file name and अगर it माला_लो loaded by
 * editing the following. This may be something we करो जबतक in development
 * but not necessarily something a user would ever need to use.
 */
#घोषणा DEFAULT_FW_8051_NAME_FPGA "hfi_dc8051.bin"
#घोषणा DEFAULT_FW_8051_NAME_ASIC "hfi1_dc8051.fw"
#घोषणा DEFAULT_FW_FABRIC_NAME "hfi1_fabric.fw"
#घोषणा DEFAULT_FW_SBUS_NAME "hfi1_sbus.fw"
#घोषणा DEFAULT_FW_PCIE_NAME "hfi1_pcie.fw"
#घोषणा ALT_FW_8051_NAME_ASIC "hfi1_dc8051_d.fw"
#घोषणा ALT_FW_FABRIC_NAME "hfi1_fabric_d.fw"
#घोषणा ALT_FW_SBUS_NAME "hfi1_sbus_d.fw"
#घोषणा ALT_FW_PCIE_NAME "hfi1_pcie_d.fw"

MODULE_FIRMWARE(DEFAULT_FW_8051_NAME_ASIC);
MODULE_FIRMWARE(DEFAULT_FW_FABRIC_NAME);
MODULE_FIRMWARE(DEFAULT_FW_SBUS_NAME);
MODULE_FIRMWARE(DEFAULT_FW_PCIE_NAME);

अटल uपूर्णांक fw_8051_load = 1;
अटल uपूर्णांक fw_fabric_serdes_load = 1;
अटल uपूर्णांक fw_pcie_serdes_load = 1;
अटल uपूर्णांक fw_sbus_load = 1;

/* Firmware file names get set in hfi1_firmware_init() based on the above */
अटल अक्षर *fw_8051_name;
अटल अक्षर *fw_fabric_serdes_name;
अटल अक्षर *fw_sbus_name;
अटल अक्षर *fw_pcie_serdes_name;

#घोषणा SBUS_MAX_POLL_COUNT 100
#घोषणा SBUS_COUNTER(reg, name) \
	(((reg) >> ASIC_STS_SBUS_COUNTERS_##name##_CNT_SHIFT) & \
	 ASIC_STS_SBUS_COUNTERS_##name##_CNT_MASK)

/*
 * Firmware security header.
 */
काष्ठा css_header अणु
	u32 module_type;
	u32 header_len;
	u32 header_version;
	u32 module_id;
	u32 module_venकरोr;
	u32 date;		/* BCD yyyymmdd */
	u32 size;		/* in DWORDs */
	u32 key_size;		/* in DWORDs */
	u32 modulus_size;	/* in DWORDs */
	u32 exponent_size;	/* in DWORDs */
	u32 reserved[22];
पूर्ण;

/* expected field values */
#घोषणा CSS_MODULE_TYPE	   0x00000006
#घोषणा CSS_HEADER_LEN	   0x000000a1
#घोषणा CSS_HEADER_VERSION 0x00010000
#घोषणा CSS_MODULE_VENDOR  0x00008086

#घोषणा KEY_SIZE      256
#घोषणा MU_SIZE		8
#घोषणा EXPONENT_SIZE	4

/* size of platक्रमm configuration partition */
#घोषणा MAX_PLATFORM_CONFIG_खाता_SIZE 4096

/* size of file of plaक्रमm configuration encoded in क्रमmat version 4 */
#घोषणा PLATFORM_CONFIG_FORMAT_4_खाता_SIZE 528

/* the file itself */
काष्ठा firmware_file अणु
	काष्ठा css_header css_header;
	u8 modulus[KEY_SIZE];
	u8 exponent[EXPONENT_SIZE];
	u8 signature[KEY_SIZE];
	u8 firmware[];
पूर्ण;

काष्ठा augmented_firmware_file अणु
	काष्ठा css_header css_header;
	u8 modulus[KEY_SIZE];
	u8 exponent[EXPONENT_SIZE];
	u8 signature[KEY_SIZE];
	u8 r2[KEY_SIZE];
	u8 mu[MU_SIZE];
	u8 firmware[];
पूर्ण;

/* augmented file size dअगरference */
#घोषणा AUGMENT_SIZE (माप(काष्ठा augmented_firmware_file) - \
						माप(काष्ठा firmware_file))

काष्ठा firmware_details अणु
	/* Linux core piece */
	स्थिर काष्ठा firmware *fw;

	काष्ठा css_header *css_header;
	u8 *firmware_ptr;		/* poपूर्णांकer to binary data */
	u32 firmware_len;		/* length in bytes */
	u8 *modulus;			/* poपूर्णांकer to the modulus */
	u8 *exponent;			/* poपूर्णांकer to the exponent */
	u8 *signature;			/* poपूर्णांकer to the signature */
	u8 *r2;				/* poपूर्णांकer to r2 */
	u8 *mu;				/* poपूर्णांकer to mu */
	काष्ठा augmented_firmware_file dummy_header;
पूर्ण;

/*
 * The mutex protects fw_state, fw_err, and all of the firmware_details
 * variables.
 */
अटल DEFINE_MUTEX(fw_mutex);
क्रमागत fw_state अणु
	FW_EMPTY,
	FW_TRY,
	FW_FINAL,
	FW_ERR
पूर्ण;

अटल क्रमागत fw_state fw_state = FW_EMPTY;
अटल पूर्णांक fw_err;
अटल काष्ठा firmware_details fw_8051;
अटल काष्ठा firmware_details fw_fabric;
अटल काष्ठा firmware_details fw_pcie;
अटल काष्ठा firmware_details fw_sbus;

/* flags क्रम turn_off_spicos() */
#घोषणा SPICO_SBUS   0x1
#घोषणा SPICO_FABRIC 0x2
#घोषणा ENABLE_SPICO_SMASK 0x1

/* security block commands */
#घोषणा RSA_CMD_INIT  0x1
#घोषणा RSA_CMD_START 0x2

/* security block status */
#घोषणा RSA_STATUS_IDLE   0x0
#घोषणा RSA_STATUS_ACTIVE 0x1
#घोषणा RSA_STATUS_DONE   0x2
#घोषणा RSA_STATUS_FAILED 0x3

/* RSA engine समयout, in ms */
#घोषणा RSA_ENGINE_TIMEOUT 100 /* ms */

/* hardware mutex समयout, in ms */
#घोषणा HM_TIMEOUT 10 /* ms */

/* 8051 memory access समयout, in us */
#घोषणा DC8051_ACCESS_TIMEOUT 100 /* us */

/* the number of fabric SerDes on the SBus */
#घोषणा NUM_FABRIC_SERDES 4

/* ASIC_STS_SBUS_RESULT.RESULT_CODE value */
#घोषणा SBUS_READ_COMPLETE 0x4

/* SBus fabric SerDes addresses, one set per HFI */
अटल स्थिर u8 fabric_serdes_addrs[2][NUM_FABRIC_SERDES] = अणु
	अणु 0x01, 0x02, 0x03, 0x04 पूर्ण,
	अणु 0x28, 0x29, 0x2a, 0x2b पूर्ण
पूर्ण;

/* SBus PCIe SerDes addresses, one set per HFI */
अटल स्थिर u8 pcie_serdes_addrs[2][NUM_PCIE_SERDES] = अणु
	अणु 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 0x16,
	  0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26 पूर्ण,
	अणु 0x2f, 0x31, 0x33, 0x35, 0x37, 0x39, 0x3b, 0x3d,
	  0x3f, 0x41, 0x43, 0x45, 0x47, 0x49, 0x4b, 0x4d पूर्ण
पूर्ण;

/* SBus PCIe PCS addresses, one set per HFI */
स्थिर u8 pcie_pcs_addrs[2][NUM_PCIE_SERDES] = अणु
	अणु 0x09, 0x0b, 0x0d, 0x0f, 0x11, 0x13, 0x15, 0x17,
	  0x19, 0x1b, 0x1d, 0x1f, 0x21, 0x23, 0x25, 0x27 पूर्ण,
	अणु 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e,
	  0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e पूर्ण
पूर्ण;

/* SBus fabric SerDes broadcast addresses, one per HFI */
अटल स्थिर u8 fabric_serdes_broadcast[2] = अणु 0xe4, 0xe5 पूर्ण;
अटल स्थिर u8 all_fabric_serdes_broadcast = 0xe1;

/* SBus PCIe SerDes broadcast addresses, one per HFI */
स्थिर u8 pcie_serdes_broadcast[2] = अणु 0xe2, 0xe3 पूर्ण;
अटल स्थिर u8 all_pcie_serdes_broadcast = 0xe0;

अटल स्थिर u32 platक्रमm_config_table_limits[PLATFORM_CONFIG_TABLE_MAX] = अणु
	0,
	SYSTEM_TABLE_MAX,
	PORT_TABLE_MAX,
	RX_PRESET_TABLE_MAX,
	TX_PRESET_TABLE_MAX,
	QSFP_ATTEN_TABLE_MAX,
	VARIABLE_SETTINGS_TABLE_MAX
पूर्ण;

/* क्रमwards */
अटल व्योम dispose_one_firmware(काष्ठा firmware_details *fdet);
अटल पूर्णांक load_fabric_serdes_firmware(काष्ठा hfi1_devdata *dd,
				       काष्ठा firmware_details *fdet);
अटल व्योम dump_fw_version(काष्ठा hfi1_devdata *dd);

/*
 * Read a single 64-bit value from 8051 data memory.
 *
 * Expects:
 * o caller to have alपढ़ोy set up data पढ़ो, no स्वतः increment
 * o caller to turn off पढ़ो enable when finished
 *
 * The address argument is a byte offset.  Bits 0:2 in the address are
 * ignored - i.e. the hardware will always करो aligned 8-byte पढ़ोs as अगर
 * the lower bits are zero.
 *
 * Return 0 on success, -ENXIO on a पढ़ो error (समयout).
 */
अटल पूर्णांक __पढ़ो_8051_data(काष्ठा hfi1_devdata *dd, u32 addr, u64 *result)
अणु
	u64 reg;
	पूर्णांक count;

	/* step 1: set the address, clear enable */
	reg = (addr & DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_MASK)
			<< DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_SHIFT;
	ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL, reg);
	/* step 2: enable */
	ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL,
		  reg | DC_DC8051_CFG_RAM_ACCESS_CTRL_READ_ENA_SMASK);

	/* रुको until ACCESS_COMPLETED is set */
	count = 0;
	जबतक ((पढ़ो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_STATUS)
		    & DC_DC8051_CFG_RAM_ACCESS_STATUS_ACCESS_COMPLETED_SMASK)
		    == 0) अणु
		count++;
		अगर (count > DC8051_ACCESS_TIMEOUT) अणु
			dd_dev_err(dd, "timeout reading 8051 data\n");
			वापस -ENXIO;
		पूर्ण
		ndelay(10);
	पूर्ण

	/* gather the data */
	*result = पढ़ो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_RD_DATA);

	वापस 0;
पूर्ण

/*
 * Read 8051 data starting at addr, क्रम len bytes.  Will पढ़ो in 8-byte chunks.
 * Return 0 on success, -त्रुटि_सं on error.
 */
पूर्णांक पढ़ो_8051_data(काष्ठा hfi1_devdata *dd, u32 addr, u32 len, u64 *result)
अणु
	अचिन्हित दीर्घ flags;
	u32 करोne;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&dd->dc8051_memlock, flags);

	/* data पढ़ो set-up, no स्वतः-increment */
	ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_SETUP, 0);

	क्रम (करोne = 0; करोne < len; addr += 8, करोne += 8, result++) अणु
		ret = __पढ़ो_8051_data(dd, addr, result);
		अगर (ret)
			अवरोध;
	पूर्ण

	/* turn off पढ़ो enable */
	ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL, 0);

	spin_unlock_irqrestore(&dd->dc8051_memlock, flags);

	वापस ret;
पूर्ण

/*
 * Write data or code to the 8051 code or data RAM.
 */
अटल पूर्णांक ग_लिखो_8051(काष्ठा hfi1_devdata *dd, पूर्णांक code, u32 start,
		      स्थिर u8 *data, u32 len)
अणु
	u64 reg;
	u32 offset;
	पूर्णांक aligned, count;

	/* check alignment */
	aligned = ((अचिन्हित दीर्घ)data & 0x7) == 0;

	/* ग_लिखो set-up */
	reg = (code ? DC_DC8051_CFG_RAM_ACCESS_SETUP_RAM_SEL_SMASK : 0ull)
		| DC_DC8051_CFG_RAM_ACCESS_SETUP_AUTO_INCR_ADDR_SMASK;
	ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_SETUP, reg);

	reg = ((start & DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_MASK)
			<< DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_SHIFT)
		| DC_DC8051_CFG_RAM_ACCESS_CTRL_WRITE_ENA_SMASK;
	ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL, reg);

	/* ग_लिखो */
	क्रम (offset = 0; offset < len; offset += 8) अणु
		पूर्णांक bytes = len - offset;

		अगर (bytes < 8) अणु
			reg = 0;
			स_नकल(&reg, &data[offset], bytes);
		पूर्ण अन्यथा अगर (aligned) अणु
			reg = *(u64 *)&data[offset];
		पूर्ण अन्यथा अणु
			स_नकल(&reg, &data[offset], 8);
		पूर्ण
		ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_WR_DATA, reg);

		/* रुको until ACCESS_COMPLETED is set */
		count = 0;
		जबतक ((पढ़ो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_STATUS)
		    & DC_DC8051_CFG_RAM_ACCESS_STATUS_ACCESS_COMPLETED_SMASK)
		    == 0) अणु
			count++;
			अगर (count > DC8051_ACCESS_TIMEOUT) अणु
				dd_dev_err(dd, "timeout writing 8051 data\n");
				वापस -ENXIO;
			पूर्ण
			udelay(1);
		पूर्ण
	पूर्ण

	/* turn off ग_लिखो access, स्वतः increment (also sets to data access) */
	ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL, 0);
	ग_लिखो_csr(dd, DC_DC8051_CFG_RAM_ACCESS_SETUP, 0);

	वापस 0;
पूर्ण

/* वापस 0 अगर values match, non-zero and complain otherwise */
अटल पूर्णांक invalid_header(काष्ठा hfi1_devdata *dd, स्थिर अक्षर *what,
			  u32 actual, u32 expected)
अणु
	अगर (actual == expected)
		वापस 0;

	dd_dev_err(dd,
		   "invalid firmware header field %s: expected 0x%x, actual 0x%x\n",
		   what, expected, actual);
	वापस 1;
पूर्ण

/*
 * Verअगरy that the अटल fields in the CSS header match.
 */
अटल पूर्णांक verअगरy_css_header(काष्ठा hfi1_devdata *dd, काष्ठा css_header *css)
अणु
	/* verअगरy CSS header fields (most sizes are in DW, so add /4) */
	अगर (invalid_header(dd, "module_type", css->module_type,
			   CSS_MODULE_TYPE) ||
	    invalid_header(dd, "header_len", css->header_len,
			   (माप(काष्ठा firmware_file) / 4)) ||
	    invalid_header(dd, "header_version", css->header_version,
			   CSS_HEADER_VERSION) ||
	    invalid_header(dd, "module_vendor", css->module_venकरोr,
			   CSS_MODULE_VENDOR) ||
	    invalid_header(dd, "key_size", css->key_size, KEY_SIZE / 4) ||
	    invalid_header(dd, "modulus_size", css->modulus_size,
			   KEY_SIZE / 4) ||
	    invalid_header(dd, "exponent_size", css->exponent_size,
			   EXPONENT_SIZE / 4)) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Make sure there are at least some bytes after the prefix.
 */
अटल पूर्णांक payload_check(काष्ठा hfi1_devdata *dd, स्थिर अक्षर *name,
			 दीर्घ file_size, दीर्घ prefix_size)
अणु
	/* make sure we have some payload */
	अगर (prefix_size >= file_size) अणु
		dd_dev_err(dd,
			   "firmware \"%s\", size %ld, must be larger than %ld bytes\n",
			   name, file_size, prefix_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Request the firmware from the प्रणाली.  Extract the pieces and fill in
 * fdet.  If successful, the caller will need to call dispose_one_firmware().
 * Returns 0 on success, -ERRNO on error.
 */
अटल पूर्णांक obtain_one_firmware(काष्ठा hfi1_devdata *dd, स्थिर अक्षर *name,
			       काष्ठा firmware_details *fdet)
अणु
	काष्ठा css_header *css;
	पूर्णांक ret;

	स_रखो(fdet, 0, माप(*fdet));

	ret = request_firmware(&fdet->fw, name, &dd->pcidev->dev);
	अगर (ret) अणु
		dd_dev_warn(dd, "cannot find firmware \"%s\", err %d\n",
			    name, ret);
		वापस ret;
	पूर्ण

	/* verअगरy the firmware */
	अगर (fdet->fw->size < माप(काष्ठा css_header)) अणु
		dd_dev_err(dd, "firmware \"%s\" is too small\n", name);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	css = (काष्ठा css_header *)fdet->fw->data;

	hfi1_cdbg(FIRMWARE, "Firmware %s details:", name);
	hfi1_cdbg(FIRMWARE, "file size: 0x%lx bytes", fdet->fw->size);
	hfi1_cdbg(FIRMWARE, "CSS structure:");
	hfi1_cdbg(FIRMWARE, "  module_type    0x%x", css->module_type);
	hfi1_cdbg(FIRMWARE, "  header_len     0x%03x (0x%03x bytes)",
		  css->header_len, 4 * css->header_len);
	hfi1_cdbg(FIRMWARE, "  header_version 0x%x", css->header_version);
	hfi1_cdbg(FIRMWARE, "  module_id      0x%x", css->module_id);
	hfi1_cdbg(FIRMWARE, "  module_vendor  0x%x", css->module_venकरोr);
	hfi1_cdbg(FIRMWARE, "  date           0x%x", css->date);
	hfi1_cdbg(FIRMWARE, "  size           0x%03x (0x%03x bytes)",
		  css->size, 4 * css->size);
	hfi1_cdbg(FIRMWARE, "  key_size       0x%03x (0x%03x bytes)",
		  css->key_size, 4 * css->key_size);
	hfi1_cdbg(FIRMWARE, "  modulus_size   0x%03x (0x%03x bytes)",
		  css->modulus_size, 4 * css->modulus_size);
	hfi1_cdbg(FIRMWARE, "  exponent_size  0x%03x (0x%03x bytes)",
		  css->exponent_size, 4 * css->exponent_size);
	hfi1_cdbg(FIRMWARE, "firmware size: 0x%lx bytes",
		  fdet->fw->size - माप(काष्ठा firmware_file));

	/*
	 * If the file करोes not have a valid CSS header, fail.
	 * Otherwise, check the CSS size field क्रम an expected size.
	 * The augmented file has r2 and mu inserted after the header
	 * was generated, so there will be a known dअगरference between
	 * the CSS header size and the actual file size.  Use this
	 * dअगरference to identअगरy an augmented file.
	 *
	 * Note: css->size is in DWORDs, multiply by 4 to get bytes.
	 */
	ret = verअगरy_css_header(dd, css);
	अगर (ret) अणु
		dd_dev_info(dd, "Invalid CSS header for \"%s\"\n", name);
	पूर्ण अन्यथा अगर ((css->size * 4) == fdet->fw->size) अणु
		/* non-augmented firmware file */
		काष्ठा firmware_file *ff = (काष्ठा firmware_file *)
							fdet->fw->data;

		/* make sure there are bytes in the payload */
		ret = payload_check(dd, name, fdet->fw->size,
				    माप(काष्ठा firmware_file));
		अगर (ret == 0) अणु
			fdet->css_header = css;
			fdet->modulus = ff->modulus;
			fdet->exponent = ff->exponent;
			fdet->signature = ff->signature;
			fdet->r2 = fdet->dummy_header.r2; /* use dummy space */
			fdet->mu = fdet->dummy_header.mu; /* use dummy space */
			fdet->firmware_ptr = ff->firmware;
			fdet->firmware_len = fdet->fw->size -
						माप(काष्ठा firmware_file);
			/*
			 * Header करोes not include r2 and mu - generate here.
			 * For now, fail.
			 */
			dd_dev_err(dd, "driver is unable to validate firmware without r2 and mu (not in firmware file)\n");
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर ((css->size * 4) + AUGMENT_SIZE == fdet->fw->size) अणु
		/* augmented firmware file */
		काष्ठा augmented_firmware_file *aff =
			(काष्ठा augmented_firmware_file *)fdet->fw->data;

		/* make sure there are bytes in the payload */
		ret = payload_check(dd, name, fdet->fw->size,
				    माप(काष्ठा augmented_firmware_file));
		अगर (ret == 0) अणु
			fdet->css_header = css;
			fdet->modulus = aff->modulus;
			fdet->exponent = aff->exponent;
			fdet->signature = aff->signature;
			fdet->r2 = aff->r2;
			fdet->mu = aff->mu;
			fdet->firmware_ptr = aff->firmware;
			fdet->firmware_len = fdet->fw->size -
					माप(काष्ठा augmented_firmware_file);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* css->size check failed */
		dd_dev_err(dd,
			   "invalid firmware header field size: expected 0x%lx or 0x%lx, actual 0x%x\n",
			   fdet->fw->size / 4,
			   (fdet->fw->size - AUGMENT_SIZE) / 4,
			   css->size);

		ret = -EINVAL;
	पूर्ण

करोne:
	/* अगर वापसing an error, clean up after ourselves */
	अगर (ret)
		dispose_one_firmware(fdet);
	वापस ret;
पूर्ण

अटल व्योम dispose_one_firmware(काष्ठा firmware_details *fdet)
अणु
	release_firmware(fdet->fw);
	/* erase all previous inक्रमmation */
	स_रखो(fdet, 0, माप(*fdet));
पूर्ण

/*
 * Obtain the 4 firmwares from the OS.  All must be obtained at once or not
 * at all.  If called with the firmware state in FW_TRY, use alternate names.
 * On निकास, this routine will have set the firmware state to one of FW_TRY,
 * FW_FINAL, or FW_ERR.
 *
 * Must be holding fw_mutex.
 */
अटल व्योम __obtain_firmware(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक err = 0;

	अगर (fw_state == FW_FINAL)	/* nothing more to obtain */
		वापस;
	अगर (fw_state == FW_ERR)		/* alपढ़ोy in error */
		वापस;

	/* fw_state is FW_EMPTY or FW_TRY */
retry:
	अगर (fw_state == FW_TRY) अणु
		/*
		 * We tried the original and it failed.  Move to the
		 * alternate.
		 */
		dd_dev_warn(dd, "using alternate firmware names\n");
		/*
		 * Let others run.  Some प्रणालीs, when missing firmware, करोes
		 * something that holds क्रम 30 seconds.  If we करो that twice
		 * in a row it triggers task blocked warning.
		 */
		cond_resched();
		अगर (fw_8051_load)
			dispose_one_firmware(&fw_8051);
		अगर (fw_fabric_serdes_load)
			dispose_one_firmware(&fw_fabric);
		अगर (fw_sbus_load)
			dispose_one_firmware(&fw_sbus);
		अगर (fw_pcie_serdes_load)
			dispose_one_firmware(&fw_pcie);
		fw_8051_name = ALT_FW_8051_NAME_ASIC;
		fw_fabric_serdes_name = ALT_FW_FABRIC_NAME;
		fw_sbus_name = ALT_FW_SBUS_NAME;
		fw_pcie_serdes_name = ALT_FW_PCIE_NAME;

		/*
		 * Add a delay beक्रमe obtaining and loading debug firmware.
		 * Authorization will fail अगर the delay between firmware
		 * authorization events is लघुer than 50us. Add 100us to
		 * make a delay समय safe.
		 */
		usleep_range(100, 120);
	पूर्ण

	अगर (fw_sbus_load) अणु
		err = obtain_one_firmware(dd, fw_sbus_name, &fw_sbus);
		अगर (err)
			जाओ करोne;
	पूर्ण

	अगर (fw_pcie_serdes_load) अणु
		err = obtain_one_firmware(dd, fw_pcie_serdes_name, &fw_pcie);
		अगर (err)
			जाओ करोne;
	पूर्ण

	अगर (fw_fabric_serdes_load) अणु
		err = obtain_one_firmware(dd, fw_fabric_serdes_name,
					  &fw_fabric);
		अगर (err)
			जाओ करोne;
	पूर्ण

	अगर (fw_8051_load) अणु
		err = obtain_one_firmware(dd, fw_8051_name, &fw_8051);
		अगर (err)
			जाओ करोne;
	पूर्ण

करोne:
	अगर (err) अणु
		/* oops, had problems obtaining a firmware */
		अगर (fw_state == FW_EMPTY && dd->icode == ICODE_RTL_SILICON) अणु
			/* retry with alternate (RTL only) */
			fw_state = FW_TRY;
			जाओ retry;
		पूर्ण
		dd_dev_err(dd, "unable to obtain working firmware\n");
		fw_state = FW_ERR;
		fw_err = -ENOENT;
	पूर्ण अन्यथा अणु
		/* success */
		अगर (fw_state == FW_EMPTY &&
		    dd->icode != ICODE_FUNCTIONAL_SIMULATOR)
			fw_state = FW_TRY;	/* may retry later */
		अन्यथा
			fw_state = FW_FINAL;	/* cannot try again */
	पूर्ण
पूर्ण

/*
 * Called by all HFIs when loading their firmware - i.e. device probe समय.
 * The first one will करो the actual firmware load.  Use a mutex to resolve
 * any possible race condition.
 *
 * The call to this routine cannot be moved to driver load because the kernel
 * call request_firmware() requires a device which is only available after
 * the first device probe.
 */
अटल पूर्णांक obtain_firmware(काष्ठा hfi1_devdata *dd)
अणु
	अचिन्हित दीर्घ समयout;

	mutex_lock(&fw_mutex);

	/* 40s delay due to दीर्घ delay on missing firmware on some प्रणालीs */
	समयout = jअगरfies + msecs_to_jअगरfies(40000);
	जबतक (fw_state == FW_TRY) अणु
		/*
		 * Another device is trying the firmware.  Wait until it
		 * decides what works (or not).
		 */
		अगर (समय_after(jअगरfies, समयout)) अणु
			/* रुकोed too दीर्घ */
			dd_dev_err(dd, "Timeout waiting for firmware try");
			fw_state = FW_ERR;
			fw_err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		mutex_unlock(&fw_mutex);
		msleep(20);	/* arbitrary delay */
		mutex_lock(&fw_mutex);
	पूर्ण
	/* not in FW_TRY state */

	/* set fw_state to FW_TRY, FW_FINAL, or FW_ERR, and fw_err */
	अगर (fw_state == FW_EMPTY)
		__obtain_firmware(dd);

	mutex_unlock(&fw_mutex);
	वापस fw_err;
पूर्ण

/*
 * Called when the driver unloads.  The timing is asymmetric with its
 * counterpart, obtain_firmware().  If called at device हटाओ समय,
 * then it is conceivable that another device could probe जबतक the
 * firmware is being disposed.  The mutexes can be moved to करो that
 * safely, but then the firmware would be requested from the OS multiple
 * बार.
 *
 * No mutex is needed as the driver is unloading and there cannot be any
 * other callers.
 */
व्योम dispose_firmware(व्योम)
अणु
	dispose_one_firmware(&fw_8051);
	dispose_one_firmware(&fw_fabric);
	dispose_one_firmware(&fw_pcie);
	dispose_one_firmware(&fw_sbus);

	/* retain the error state, otherwise revert to empty */
	अगर (fw_state != FW_ERR)
		fw_state = FW_EMPTY;
पूर्ण

/*
 * Called with the result of a firmware करोwnload.
 *
 * Return 1 to retry loading the firmware, 0 to stop.
 */
अटल पूर्णांक retry_firmware(काष्ठा hfi1_devdata *dd, पूर्णांक load_result)
अणु
	पूर्णांक retry;

	mutex_lock(&fw_mutex);

	अगर (load_result == 0) अणु
		/*
		 * The load succeeded, so expect all others to करो the same.
		 * Do not retry again.
		 */
		अगर (fw_state == FW_TRY)
			fw_state = FW_FINAL;
		retry = 0;	/* करो NOT retry */
	पूर्ण अन्यथा अगर (fw_state == FW_TRY) अणु
		/* load failed, obtain alternate firmware */
		__obtain_firmware(dd);
		retry = (fw_state == FW_FINAL);
	पूर्ण अन्यथा अणु
		/* अन्यथा in FW_FINAL or FW_ERR, no retry in either हाल */
		retry = 0;
	पूर्ण

	mutex_unlock(&fw_mutex);
	वापस retry;
पूर्ण

/*
 * Write a block of data to a given array CSR.  All calls will be in
 * multiples of 8 bytes.
 */
अटल व्योम ग_लिखो_rsa_data(काष्ठा hfi1_devdata *dd, पूर्णांक what,
			   स्थिर u8 *data, पूर्णांक nbytes)
अणु
	पूर्णांक qw_size = nbytes / 8;
	पूर्णांक i;

	अगर (((अचिन्हित दीर्घ)data & 0x7) == 0) अणु
		/* aligned */
		u64 *ptr = (u64 *)data;

		क्रम (i = 0; i < qw_size; i++, ptr++)
			ग_लिखो_csr(dd, what + (8 * i), *ptr);
	पूर्ण अन्यथा अणु
		/* not aligned */
		क्रम (i = 0; i < qw_size; i++, data += 8) अणु
			u64 value;

			स_नकल(&value, data, 8);
			ग_लिखो_csr(dd, what + (8 * i), value);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Write a block of data to a given CSR as a stream of ग_लिखोs.  All calls will
 * be in multiples of 8 bytes.
 */
अटल व्योम ग_लिखो_streamed_rsa_data(काष्ठा hfi1_devdata *dd, पूर्णांक what,
				    स्थिर u8 *data, पूर्णांक nbytes)
अणु
	u64 *ptr = (u64 *)data;
	पूर्णांक qw_size = nbytes / 8;

	क्रम (; qw_size > 0; qw_size--, ptr++)
		ग_लिखो_csr(dd, what, *ptr);
पूर्ण

/*
 * Download the signature and start the RSA mechanism.  Wait क्रम
 * RSA_ENGINE_TIMEOUT beक्रमe giving up.
 */
अटल पूर्णांक run_rsa(काष्ठा hfi1_devdata *dd, स्थिर अक्षर *who,
		   स्थिर u8 *signature)
अणु
	अचिन्हित दीर्घ समयout;
	u64 reg;
	u32 status;
	पूर्णांक ret = 0;

	/* ग_लिखो the signature */
	ग_लिखो_rsa_data(dd, MISC_CFG_RSA_SIGNATURE, signature, KEY_SIZE);

	/* initialize RSA */
	ग_लिखो_csr(dd, MISC_CFG_RSA_CMD, RSA_CMD_INIT);

	/*
	 * Make sure the engine is idle and insert a delay between the two
	 * ग_लिखोs to MISC_CFG_RSA_CMD.
	 */
	status = (पढ़ो_csr(dd, MISC_CFG_FW_CTRL)
			   & MISC_CFG_FW_CTRL_RSA_STATUS_SMASK)
			     >> MISC_CFG_FW_CTRL_RSA_STATUS_SHIFT;
	अगर (status != RSA_STATUS_IDLE) अणु
		dd_dev_err(dd, "%s security engine not idle - giving up\n",
			   who);
		वापस -EBUSY;
	पूर्ण

	/* start RSA */
	ग_लिखो_csr(dd, MISC_CFG_RSA_CMD, RSA_CMD_START);

	/*
	 * Look क्रम the result.
	 *
	 * The RSA engine is hooked up to two MISC errors.  The driver
	 * masks these errors as they करो not respond to the standard
	 * error "clear down" mechanism.  Look क्रम these errors here and
	 * clear them when possible.  This routine will निकास with the
	 * errors of the current run still set.
	 *
	 * MISC_FW_AUTH_FAILED_ERR
	 *	Firmware authorization failed.  This can be cleared by
	 *	re-initializing the RSA engine, then clearing the status bit.
	 *	Do not re-init the RSA angine immediately after a successful
	 *	run - this will reset the current authorization.
	 *
	 * MISC_KEY_MISMATCH_ERR
	 *	Key करोes not match.  The only way to clear this is to load
	 *	a matching key then clear the status bit.  If this error
	 *	is उठाओd, it will persist outside of this routine until a
	 *	matching key is loaded.
	 */
	समयout = msecs_to_jअगरfies(RSA_ENGINE_TIMEOUT) + jअगरfies;
	जबतक (1) अणु
		status = (पढ़ो_csr(dd, MISC_CFG_FW_CTRL)
			   & MISC_CFG_FW_CTRL_RSA_STATUS_SMASK)
			     >> MISC_CFG_FW_CTRL_RSA_STATUS_SHIFT;

		अगर (status == RSA_STATUS_IDLE) अणु
			/* should not happen */
			dd_dev_err(dd, "%s firmware security bad idle state\n",
				   who);
			ret = -EINVAL;
			अवरोध;
		पूर्ण अन्यथा अगर (status == RSA_STATUS_DONE) अणु
			/* finished successfully */
			अवरोध;
		पूर्ण अन्यथा अगर (status == RSA_STATUS_FAILED) अणु
			/* finished unsuccessfully */
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		/* अन्यथा still active */

		अगर (समय_after(jअगरfies, समयout)) अणु
			/*
			 * Timed out जबतक active.  We can't reset the engine
			 * अगर it is stuck active, but run through the
			 * error code to see what error bits are set.
			 */
			dd_dev_err(dd, "%s firmware security time out\n", who);
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		msleep(20);
	पूर्ण

	/*
	 * Arrive here on success or failure.  Clear all RSA engine
	 * errors.  All current errors will stick - the RSA logic is keeping
	 * error high.  All previous errors will clear - the RSA logic
	 * is not keeping the error high.
	 */
	ग_लिखो_csr(dd, MISC_ERR_CLEAR,
		  MISC_ERR_STATUS_MISC_FW_AUTH_FAILED_ERR_SMASK |
		  MISC_ERR_STATUS_MISC_KEY_MISMATCH_ERR_SMASK);
	/*
	 * All that is left are the current errors.  Prपूर्णांक warnings on
	 * authorization failure details, अगर any.  Firmware authorization
	 * can be retried, so these are only warnings.
	 */
	reg = पढ़ो_csr(dd, MISC_ERR_STATUS);
	अगर (ret) अणु
		अगर (reg & MISC_ERR_STATUS_MISC_FW_AUTH_FAILED_ERR_SMASK)
			dd_dev_warn(dd, "%s firmware authorization failed\n",
				    who);
		अगर (reg & MISC_ERR_STATUS_MISC_KEY_MISMATCH_ERR_SMASK)
			dd_dev_warn(dd, "%s firmware key mismatch\n", who);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम load_security_variables(काष्ठा hfi1_devdata *dd,
				    काष्ठा firmware_details *fdet)
अणु
	/* Security variables a.  Write the modulus */
	ग_लिखो_rsa_data(dd, MISC_CFG_RSA_MODULUS, fdet->modulus, KEY_SIZE);
	/* Security variables b.  Write the r2 */
	ग_लिखो_rsa_data(dd, MISC_CFG_RSA_R2, fdet->r2, KEY_SIZE);
	/* Security variables c.  Write the mu */
	ग_लिखो_rsa_data(dd, MISC_CFG_RSA_MU, fdet->mu, MU_SIZE);
	/* Security variables d.  Write the header */
	ग_लिखो_streamed_rsa_data(dd, MISC_CFG_SHA_PRELOAD,
				(u8 *)fdet->css_header,
				माप(काष्ठा css_header));
पूर्ण

/* वापस the 8051 firmware state */
अटल अंतरभूत u32 get_firmware_state(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg = पढ़ो_csr(dd, DC_DC8051_STS_CUR_STATE);

	वापस (reg >> DC_DC8051_STS_CUR_STATE_FIRMWARE_SHIFT)
				& DC_DC8051_STS_CUR_STATE_FIRMWARE_MASK;
पूर्ण

/*
 * Wait until the firmware is up and पढ़ोy to take host requests.
 * Return 0 on success, -ETIMEDOUT on समयout.
 */
पूर्णांक रुको_fm_पढ़ोy(काष्ठा hfi1_devdata *dd, u32 msसमयout)
अणु
	अचिन्हित दीर्घ समयout;

	/* in the simulator, the fake 8051 is always पढ़ोy */
	अगर (dd->icode == ICODE_FUNCTIONAL_SIMULATOR)
		वापस 0;

	समयout = msecs_to_jअगरfies(msसमयout) + jअगरfies;
	जबतक (1) अणु
		अगर (get_firmware_state(dd) == 0xa0)	/* पढ़ोy */
			वापस 0;
		अगर (समय_after(jअगरfies, समयout))	/* समयd out */
			वापस -ETIMEDOUT;
		usleep_range(1950, 2050); /* sleep 2ms-ish */
	पूर्ण
पूर्ण

/*
 * Load the 8051 firmware.
 */
अटल पूर्णांक load_8051_firmware(काष्ठा hfi1_devdata *dd,
			      काष्ठा firmware_details *fdet)
अणु
	u64 reg;
	पूर्णांक ret;
	u8 ver_major;
	u8 ver_minor;
	u8 ver_patch;

	/*
	 * DC Reset sequence
	 * Load DC 8051 firmware
	 */
	/*
	 * DC reset step 1: Reset DC8051
	 */
	reg = DC_DC8051_CFG_RST_M8051W_SMASK
		| DC_DC8051_CFG_RST_CRAM_SMASK
		| DC_DC8051_CFG_RST_DRAM_SMASK
		| DC_DC8051_CFG_RST_IRAM_SMASK
		| DC_DC8051_CFG_RST_SFR_SMASK;
	ग_लिखो_csr(dd, DC_DC8051_CFG_RST, reg);

	/*
	 * DC reset step 2 (optional): Load 8051 data memory with link
	 * configuration
	 */

	/*
	 * DC reset step 3: Load DC8051 firmware
	 */
	/* release all but the core reset */
	reg = DC_DC8051_CFG_RST_M8051W_SMASK;
	ग_लिखो_csr(dd, DC_DC8051_CFG_RST, reg);

	/* Firmware load step 1 */
	load_security_variables(dd, fdet);

	/*
	 * Firmware load step 2.  Clear MISC_CFG_FW_CTRL.FW_8051_LOADED
	 */
	ग_लिखो_csr(dd, MISC_CFG_FW_CTRL, 0);

	/* Firmware load steps 3-5 */
	ret = ग_लिखो_8051(dd, 1/*code*/, 0, fdet->firmware_ptr,
			 fdet->firmware_len);
	अगर (ret)
		वापस ret;

	/*
	 * DC reset step 4. Host starts the DC8051 firmware
	 */
	/*
	 * Firmware load step 6.  Set MISC_CFG_FW_CTRL.FW_8051_LOADED
	 */
	ग_लिखो_csr(dd, MISC_CFG_FW_CTRL, MISC_CFG_FW_CTRL_FW_8051_LOADED_SMASK);

	/* Firmware load steps 7-10 */
	ret = run_rsa(dd, "8051", fdet->signature);
	अगर (ret)
		वापस ret;

	/* clear all reset bits, releasing the 8051 */
	ग_लिखो_csr(dd, DC_DC8051_CFG_RST, 0ull);

	/*
	 * DC reset step 5. Wait क्रम firmware to be पढ़ोy to accept host
	 * requests.
	 */
	ret = रुको_fm_पढ़ोy(dd, TIMEOUT_8051_START);
	अगर (ret) अणु /* समयd out */
		dd_dev_err(dd, "8051 start timeout, current state 0x%x\n",
			   get_firmware_state(dd));
		वापस -ETIMEDOUT;
	पूर्ण

	पढ़ो_misc_status(dd, &ver_major, &ver_minor, &ver_patch);
	dd_dev_info(dd, "8051 firmware version %d.%d.%d\n",
		    (पूर्णांक)ver_major, (पूर्णांक)ver_minor, (पूर्णांक)ver_patch);
	dd->dc8051_ver = dc8051_ver(ver_major, ver_minor, ver_patch);
	ret = ग_लिखो_host_पूर्णांकerface_version(dd, HOST_INTERFACE_VERSION);
	अगर (ret != HCMD_SUCCESS) अणु
		dd_dev_err(dd,
			   "Failed to set host interface version, return 0x%x\n",
			   ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write the SBus request रेजिस्टर
 *
 * No need क्रम masking - the arguments are sized exactly.
 */
व्योम sbus_request(काष्ठा hfi1_devdata *dd,
		  u8 receiver_addr, u8 data_addr, u8 command, u32 data_in)
अणु
	ग_लिखो_csr(dd, ASIC_CFG_SBUS_REQUEST,
		  ((u64)data_in << ASIC_CFG_SBUS_REQUEST_DATA_IN_SHIFT) |
		  ((u64)command << ASIC_CFG_SBUS_REQUEST_COMMAND_SHIFT) |
		  ((u64)data_addr << ASIC_CFG_SBUS_REQUEST_DATA_ADDR_SHIFT) |
		  ((u64)receiver_addr <<
		   ASIC_CFG_SBUS_REQUEST_RECEIVER_ADDR_SHIFT));
पूर्ण

/*
 * Read a value from the SBus.
 *
 * Requires the caller to be in fast mode
 */
अटल u32 sbus_पढ़ो(काष्ठा hfi1_devdata *dd, u8 receiver_addr, u8 data_addr,
		     u32 data_in)
अणु
	u64 reg;
	पूर्णांक retries;
	पूर्णांक success = 0;
	u32 result = 0;
	u32 result_code = 0;

	sbus_request(dd, receiver_addr, data_addr, READ_SBUS_RECEIVER, data_in);

	क्रम (retries = 0; retries < 100; retries++) अणु
		usleep_range(1000, 1200); /* arbitrary */
		reg = पढ़ो_csr(dd, ASIC_STS_SBUS_RESULT);
		result_code = (reg >> ASIC_STS_SBUS_RESULT_RESULT_CODE_SHIFT)
				& ASIC_STS_SBUS_RESULT_RESULT_CODE_MASK;
		अगर (result_code != SBUS_READ_COMPLETE)
			जारी;

		success = 1;
		result = (reg >> ASIC_STS_SBUS_RESULT_DATA_OUT_SHIFT)
			   & ASIC_STS_SBUS_RESULT_DATA_OUT_MASK;
		अवरोध;
	पूर्ण

	अगर (!success) अणु
		dd_dev_err(dd, "%s: read failed, result code 0x%x\n", __func__,
			   result_code);
	पूर्ण

	वापस result;
पूर्ण

/*
 * Turn off the SBus and fabric serdes spicos.
 *
 * + Must be called with Sbus fast mode turned on.
 * + Must be called after fabric serdes broadcast is set up.
 * + Must be called beक्रमe the 8051 is loaded - assumes 8051 is not loaded
 *   when using MISC_CFG_FW_CTRL.
 */
अटल व्योम turn_off_spicos(काष्ठा hfi1_devdata *dd, पूर्णांक flags)
अणु
	/* only needed on A0 */
	अगर (!is_ax(dd))
		वापस;

	dd_dev_info(dd, "Turning off spicos:%s%s\n",
		    flags & SPICO_SBUS ? " SBus" : "",
		    flags & SPICO_FABRIC ? " fabric" : "");

	ग_लिखो_csr(dd, MISC_CFG_FW_CTRL, ENABLE_SPICO_SMASK);
	/* disable SBus spico */
	अगर (flags & SPICO_SBUS)
		sbus_request(dd, SBUS_MASTER_BROADCAST, 0x01,
			     WRITE_SBUS_RECEIVER, 0x00000040);

	/* disable the fabric serdes spicos */
	अगर (flags & SPICO_FABRIC)
		sbus_request(dd, fabric_serdes_broadcast[dd->hfi1_id],
			     0x07, WRITE_SBUS_RECEIVER, 0x00000000);
	ग_लिखो_csr(dd, MISC_CFG_FW_CTRL, 0);
पूर्ण

/*
 * Reset all of the fabric serdes क्रम this HFI in preparation to take the
 * link to Polling.
 *
 * To करो a reset, we need to ग_लिखो to to the serdes रेजिस्टरs.  Unक्रमtunately,
 * the fabric serdes करोwnload to the other HFI on the ASIC will have turned
 * off the firmware validation on this HFI.  This means we can't ग_लिखो to the
 * रेजिस्टरs to reset the serdes.  Work around this by perक्रमming a complete
 * re-करोwnload and validation of the fabric serdes firmware.  This, as a
 * by-product, will reset the serdes.  NOTE: the re-करोwnload requires that
 * the 8051 be in the Offline state.  I.e. not actively trying to use the
 * serdes.  This routine is called at the poपूर्णांक where the link is Offline and
 * is getting पढ़ोy to go to Polling.
 */
व्योम fabric_serdes_reset(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	अगर (!fw_fabric_serdes_load)
		वापस;

	ret = acquire_chip_resource(dd, CR_SBUS, SBUS_TIMEOUT);
	अगर (ret) अणु
		dd_dev_err(dd,
			   "Cannot acquire SBus resource to reset fabric SerDes - perhaps you should reboot\n");
		वापस;
	पूर्ण
	set_sbus_fast_mode(dd);

	अगर (is_ax(dd)) अणु
		/* A0 serdes करो not work with a re-करोwnload */
		u8 ra = fabric_serdes_broadcast[dd->hfi1_id];

		/* place SerDes in reset and disable SPICO */
		sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000011);
		/* रुको 100 refclk cycles @ 156.25MHz => 640ns */
		udelay(1);
		/* हटाओ SerDes reset */
		sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000010);
		/* turn SPICO enable on */
		sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000002);
	पूर्ण अन्यथा अणु
		turn_off_spicos(dd, SPICO_FABRIC);
		/*
		 * No need क्रम firmware retry - what to करोwnload has alपढ़ोy
		 * been decided.
		 * No need to pay attention to the load वापस - the only
		 * failure is a validation failure, which has alपढ़ोy been
		 * checked by the initial करोwnload.
		 */
		(व्योम)load_fabric_serdes_firmware(dd, &fw_fabric);
	पूर्ण

	clear_sbus_fast_mode(dd);
	release_chip_resource(dd, CR_SBUS);
पूर्ण

/* Access to the SBus in this routine should probably be serialized */
पूर्णांक sbus_request_slow(काष्ठा hfi1_devdata *dd,
		      u8 receiver_addr, u8 data_addr, u8 command, u32 data_in)
अणु
	u64 reg, count = 0;

	/* make sure fast mode is clear */
	clear_sbus_fast_mode(dd);

	sbus_request(dd, receiver_addr, data_addr, command, data_in);
	ग_लिखो_csr(dd, ASIC_CFG_SBUS_EXECUTE,
		  ASIC_CFG_SBUS_EXECUTE_EXECUTE_SMASK);
	/* Wait क्रम both DONE and RCV_DATA_VALID to go high */
	reg = पढ़ो_csr(dd, ASIC_STS_SBUS_RESULT);
	जबतक (!((reg & ASIC_STS_SBUS_RESULT_DONE_SMASK) &&
		 (reg & ASIC_STS_SBUS_RESULT_RCV_DATA_VALID_SMASK))) अणु
		अगर (count++ >= SBUS_MAX_POLL_COUNT) अणु
			u64 counts = पढ़ो_csr(dd, ASIC_STS_SBUS_COUNTERS);
			/*
			 * If the loop has समयd out, we are OK अगर DONE bit
			 * is set and RCV_DATA_VALID and EXECUTE counters
			 * are the same. If not, we cannot proceed.
			 */
			अगर ((reg & ASIC_STS_SBUS_RESULT_DONE_SMASK) &&
			    (SBUS_COUNTER(counts, RCV_DATA_VALID) ==
			     SBUS_COUNTER(counts, EXECUTE)))
				अवरोध;
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(1);
		reg = पढ़ो_csr(dd, ASIC_STS_SBUS_RESULT);
	पूर्ण
	count = 0;
	ग_लिखो_csr(dd, ASIC_CFG_SBUS_EXECUTE, 0);
	/* Wait क्रम DONE to clear after EXECUTE is cleared */
	reg = पढ़ो_csr(dd, ASIC_STS_SBUS_RESULT);
	जबतक (reg & ASIC_STS_SBUS_RESULT_DONE_SMASK) अणु
		अगर (count++ >= SBUS_MAX_POLL_COUNT)
			वापस -ETIME;
		udelay(1);
		reg = पढ़ो_csr(dd, ASIC_STS_SBUS_RESULT);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक load_fabric_serdes_firmware(काष्ठा hfi1_devdata *dd,
				       काष्ठा firmware_details *fdet)
अणु
	पूर्णांक i, err;
	स्थिर u8 ra = fabric_serdes_broadcast[dd->hfi1_id]; /* receiver addr */

	dd_dev_info(dd, "Downloading fabric firmware\n");

	/* step 1: load security variables */
	load_security_variables(dd, fdet);
	/* step 2: place SerDes in reset and disable SPICO */
	sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000011);
	/* रुको 100 refclk cycles @ 156.25MHz => 640ns */
	udelay(1);
	/* step 3:  हटाओ SerDes reset */
	sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000010);
	/* step 4: निश्चित IMEM override */
	sbus_request(dd, ra, 0x00, WRITE_SBUS_RECEIVER, 0x40000000);
	/* step 5: करोwnload SerDes machine code */
	क्रम (i = 0; i < fdet->firmware_len; i += 4) अणु
		sbus_request(dd, ra, 0x0a, WRITE_SBUS_RECEIVER,
			     *(u32 *)&fdet->firmware_ptr[i]);
	पूर्ण
	/* step 6: IMEM override off */
	sbus_request(dd, ra, 0x00, WRITE_SBUS_RECEIVER, 0x00000000);
	/* step 7: turn ECC on */
	sbus_request(dd, ra, 0x0b, WRITE_SBUS_RECEIVER, 0x000c0000);

	/* steps 8-11: run the RSA engine */
	err = run_rsa(dd, "fabric serdes", fdet->signature);
	अगर (err)
		वापस err;

	/* step 12: turn SPICO enable on */
	sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000002);
	/* step 13: enable core hardware पूर्णांकerrupts */
	sbus_request(dd, ra, 0x08, WRITE_SBUS_RECEIVER, 0x00000000);

	वापस 0;
पूर्ण

अटल पूर्णांक load_sbus_firmware(काष्ठा hfi1_devdata *dd,
			      काष्ठा firmware_details *fdet)
अणु
	पूर्णांक i, err;
	स्थिर u8 ra = SBUS_MASTER_BROADCAST; /* receiver address */

	dd_dev_info(dd, "Downloading SBus firmware\n");

	/* step 1: load security variables */
	load_security_variables(dd, fdet);
	/* step 2: place SPICO पूर्णांकo reset and enable off */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x000000c0);
	/* step 3: हटाओ reset, enable off, IMEM_CNTRL_EN on */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000240);
	/* step 4: set starting IMEM address क्रम burst करोwnload */
	sbus_request(dd, ra, 0x03, WRITE_SBUS_RECEIVER, 0x80000000);
	/* step 5: करोwnload the SBus Master machine code */
	क्रम (i = 0; i < fdet->firmware_len; i += 4) अणु
		sbus_request(dd, ra, 0x14, WRITE_SBUS_RECEIVER,
			     *(u32 *)&fdet->firmware_ptr[i]);
	पूर्ण
	/* step 6: set IMEM_CNTL_EN off */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000040);
	/* step 7: turn ECC on */
	sbus_request(dd, ra, 0x16, WRITE_SBUS_RECEIVER, 0x000c0000);

	/* steps 8-11: run the RSA engine */
	err = run_rsa(dd, "SBus", fdet->signature);
	अगर (err)
		वापस err;

	/* step 12: set SPICO_ENABLE on */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000140);

	वापस 0;
पूर्ण

अटल पूर्णांक load_pcie_serdes_firmware(काष्ठा hfi1_devdata *dd,
				     काष्ठा firmware_details *fdet)
अणु
	पूर्णांक i;
	स्थिर u8 ra = SBUS_MASTER_BROADCAST; /* receiver address */

	dd_dev_info(dd, "Downloading PCIe firmware\n");

	/* step 1: load security variables */
	load_security_variables(dd, fdet);
	/* step 2: निश्चित single step (halts the SBus Master spico) */
	sbus_request(dd, ra, 0x05, WRITE_SBUS_RECEIVER, 0x00000001);
	/* step 3: enable XDMEM access */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000d40);
	/* step 4: load firmware पूर्णांकo SBus Master XDMEM */
	/*
	 * NOTE: the dmem address, ग_लिखो_en, and wdata are all pre-packed,
	 * we only need to pick up the bytes and ग_लिखो them
	 */
	क्रम (i = 0; i < fdet->firmware_len; i += 4) अणु
		sbus_request(dd, ra, 0x04, WRITE_SBUS_RECEIVER,
			     *(u32 *)&fdet->firmware_ptr[i]);
	पूर्ण
	/* step 5: disable XDMEM access */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000140);
	/* step 6: allow SBus Spico to run */
	sbus_request(dd, ra, 0x05, WRITE_SBUS_RECEIVER, 0x00000000);

	/*
	 * steps 7-11: run RSA, अगर it succeeds, firmware is available to
	 * be swapped
	 */
	वापस run_rsa(dd, "PCIe serdes", fdet->signature);
पूर्ण

/*
 * Set the given broadcast values on the given list of devices.
 */
अटल व्योम set_serdes_broadcast(काष्ठा hfi1_devdata *dd, u8 bg1, u8 bg2,
				 स्थिर u8 *addrs, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		/*
		 * Set BROADCAST_GROUP_1 and BROADCAST_GROUP_2, leave
		 * शेषs क्रम everything अन्यथा.  Do not पढ़ो-modअगरy-ग_लिखो,
		 * per inकाष्ठाion from the manufacturer.
		 *
		 * Register 0xfd:
		 *	bits    what
		 *	-----	---------------------------------
		 *	  0	IGNORE_BROADCAST  (शेष 0)
		 *	11:4	BROADCAST_GROUP_1 (शेष 0xff)
		 *	23:16	BROADCAST_GROUP_2 (शेष 0xff)
		 */
		sbus_request(dd, addrs[count], 0xfd, WRITE_SBUS_RECEIVER,
			     (u32)bg1 << 4 | (u32)bg2 << 16);
	पूर्ण
पूर्ण

पूर्णांक acquire_hw_mutex(काष्ठा hfi1_devdata *dd)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक try = 0;
	u8 mask = 1 << dd->hfi1_id;
	u8 user = (u8)पढ़ो_csr(dd, ASIC_CFG_MUTEX);

	अगर (user == mask) अणु
		dd_dev_info(dd,
			    "Hardware mutex already acquired, mutex mask %u\n",
			    (u32)mask);
		वापस 0;
	पूर्ण

retry:
	समयout = msecs_to_jअगरfies(HM_TIMEOUT) + jअगरfies;
	जबतक (1) अणु
		ग_लिखो_csr(dd, ASIC_CFG_MUTEX, mask);
		user = (u8)पढ़ो_csr(dd, ASIC_CFG_MUTEX);
		अगर (user == mask)
			वापस 0; /* success */
		अगर (समय_after(jअगरfies, समयout))
			अवरोध; /* समयd out */
		msleep(20);
	पूर्ण

	/* समयd out */
	dd_dev_err(dd,
		   "Unable to acquire hardware mutex, mutex mask %u, my mask %u (%s)\n",
		   (u32)user, (u32)mask, (try == 0) ? "retrying" : "giving up");

	अगर (try == 0) अणु
		/* अवरोध mutex and retry */
		ग_लिखो_csr(dd, ASIC_CFG_MUTEX, 0);
		try++;
		जाओ retry;
	पूर्ण

	वापस -EBUSY;
पूर्ण

व्योम release_hw_mutex(काष्ठा hfi1_devdata *dd)
अणु
	u8 mask = 1 << dd->hfi1_id;
	u8 user = (u8)पढ़ो_csr(dd, ASIC_CFG_MUTEX);

	अगर (user != mask)
		dd_dev_warn(dd,
			    "Unable to release hardware mutex, mutex mask %u, my mask %u\n",
			    (u32)user, (u32)mask);
	अन्यथा
		ग_लिखो_csr(dd, ASIC_CFG_MUTEX, 0);
पूर्ण

/* वापस the given resource bit(s) as a mask क्रम the given HFI */
अटल अंतरभूत u64 resource_mask(u32 hfi1_id, u32 resource)
अणु
	वापस ((u64)resource) << (hfi1_id ? CR_DYN_SHIFT : 0);
पूर्ण

अटल व्योम fail_mutex_acquire_message(काष्ठा hfi1_devdata *dd,
				       स्थिर अक्षर *func)
अणु
	dd_dev_err(dd,
		   "%s: hardware mutex stuck - suggest rebooting the machine\n",
		   func);
पूर्ण

/*
 * Acquire access to a chip resource.
 *
 * Return 0 on success, -EBUSY अगर resource busy, -EIO अगर mutex acquire failed.
 */
अटल पूर्णांक __acquire_chip_resource(काष्ठा hfi1_devdata *dd, u32 resource)
अणु
	u64 scratch0, all_bits, my_bit;
	पूर्णांक ret;

	अगर (resource & CR_DYN_MASK) अणु
		/* a dynamic resource is in use अगर either HFI has set the bit */
		अगर (dd->pcidev->device == PCI_DEVICE_ID_INTEL0 &&
		    (resource & (CR_I2C1 | CR_I2C2))) अणु
			/* discrete devices must serialize across both chains */
			all_bits = resource_mask(0, CR_I2C1 | CR_I2C2) |
					resource_mask(1, CR_I2C1 | CR_I2C2);
		पूर्ण अन्यथा अणु
			all_bits = resource_mask(0, resource) |
						resource_mask(1, resource);
		पूर्ण
		my_bit = resource_mask(dd->hfi1_id, resource);
	पूर्ण अन्यथा अणु
		/* non-dynamic resources are not split between HFIs */
		all_bits = resource;
		my_bit = resource;
	पूर्ण

	/* lock against other callers within the driver wanting a resource */
	mutex_lock(&dd->asic_data->asic_resource_mutex);

	ret = acquire_hw_mutex(dd);
	अगर (ret) अणु
		fail_mutex_acquire_message(dd, __func__);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	scratch0 = पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	अगर (scratch0 & all_bits) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		ग_लिखो_csr(dd, ASIC_CFG_SCRATCH, scratch0 | my_bit);
		/* क्रमce ग_लिखो to be visible to other HFI on another OS */
		(व्योम)पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	पूर्ण

	release_hw_mutex(dd);

करोne:
	mutex_unlock(&dd->asic_data->asic_resource_mutex);
	वापस ret;
पूर्ण

/*
 * Acquire access to a chip resource, रुको up to msरुको milliseconds क्रम
 * the resource to become available.
 *
 * Return 0 on success, -EBUSY अगर busy (even after रुको), -EIO अगर mutex
 * acquire failed.
 */
पूर्णांक acquire_chip_resource(काष्ठा hfi1_devdata *dd, u32 resource, u32 msरुको)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	समयout = jअगरfies + msecs_to_jअगरfies(msरुको);
	जबतक (1) अणु
		ret = __acquire_chip_resource(dd, resource);
		अगर (ret != -EBUSY)
			वापस ret;
		/* resource is busy, check our समयout */
		अगर (समय_after_eq(jअगरfies, समयout))
			वापस -EBUSY;
		usleep_range(80, 120);	/* arbitrary delay */
	पूर्ण
पूर्ण

/*
 * Release access to a chip resource
 */
व्योम release_chip_resource(काष्ठा hfi1_devdata *dd, u32 resource)
अणु
	u64 scratch0, bit;

	/* only dynamic resources should ever be cleared */
	अगर (!(resource & CR_DYN_MASK)) अणु
		dd_dev_err(dd, "%s: invalid resource 0x%x\n", __func__,
			   resource);
		वापस;
	पूर्ण
	bit = resource_mask(dd->hfi1_id, resource);

	/* lock against other callers within the driver wanting a resource */
	mutex_lock(&dd->asic_data->asic_resource_mutex);

	अगर (acquire_hw_mutex(dd)) अणु
		fail_mutex_acquire_message(dd, __func__);
		जाओ करोne;
	पूर्ण

	scratch0 = पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	अगर ((scratch0 & bit) != 0) अणु
		scratch0 &= ~bit;
		ग_लिखो_csr(dd, ASIC_CFG_SCRATCH, scratch0);
		/* क्रमce ग_लिखो to be visible to other HFI on another OS */
		(व्योम)पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	पूर्ण अन्यथा अणु
		dd_dev_warn(dd, "%s: id %d, resource 0x%x: bit not set\n",
			    __func__, dd->hfi1_id, resource);
	पूर्ण

	release_hw_mutex(dd);

करोne:
	mutex_unlock(&dd->asic_data->asic_resource_mutex);
पूर्ण

/*
 * Return true अगर resource is set, false otherwise.  Prपूर्णांक a warning
 * अगर not set and a function is supplied.
 */
bool check_chip_resource(काष्ठा hfi1_devdata *dd, u32 resource,
			 स्थिर अक्षर *func)
अणु
	u64 scratch0, bit;

	अगर (resource & CR_DYN_MASK)
		bit = resource_mask(dd->hfi1_id, resource);
	अन्यथा
		bit = resource;

	scratch0 = पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	अगर ((scratch0 & bit) == 0) अणु
		अगर (func)
			dd_dev_warn(dd,
				    "%s: id %d, resource 0x%x, not acquired!\n",
				    func, dd->hfi1_id, resource);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम clear_chip_resources(काष्ठा hfi1_devdata *dd, स्थिर अक्षर *func)
अणु
	u64 scratch0;

	/* lock against other callers within the driver wanting a resource */
	mutex_lock(&dd->asic_data->asic_resource_mutex);

	अगर (acquire_hw_mutex(dd)) अणु
		fail_mutex_acquire_message(dd, func);
		जाओ करोne;
	पूर्ण

	/* clear all dynamic access bits क्रम this HFI */
	scratch0 = पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	scratch0 &= ~resource_mask(dd->hfi1_id, CR_DYN_MASK);
	ग_लिखो_csr(dd, ASIC_CFG_SCRATCH, scratch0);
	/* क्रमce ग_लिखो to be visible to other HFI on another OS */
	(व्योम)पढ़ो_csr(dd, ASIC_CFG_SCRATCH);

	release_hw_mutex(dd);

करोne:
	mutex_unlock(&dd->asic_data->asic_resource_mutex);
पूर्ण

व्योम init_chip_resources(काष्ठा hfi1_devdata *dd)
अणु
	/* clear any holds left by us */
	clear_chip_resources(dd, __func__);
पूर्ण

व्योम finish_chip_resources(काष्ठा hfi1_devdata *dd)
अणु
	/* clear any holds left by us */
	clear_chip_resources(dd, __func__);
पूर्ण

व्योम set_sbus_fast_mode(काष्ठा hfi1_devdata *dd)
अणु
	ग_लिखो_csr(dd, ASIC_CFG_SBUS_EXECUTE,
		  ASIC_CFG_SBUS_EXECUTE_FAST_MODE_SMASK);
पूर्ण

व्योम clear_sbus_fast_mode(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg, count = 0;

	reg = पढ़ो_csr(dd, ASIC_STS_SBUS_COUNTERS);
	जबतक (SBUS_COUNTER(reg, EXECUTE) !=
	       SBUS_COUNTER(reg, RCV_DATA_VALID)) अणु
		अगर (count++ >= SBUS_MAX_POLL_COUNT)
			अवरोध;
		udelay(1);
		reg = पढ़ो_csr(dd, ASIC_STS_SBUS_COUNTERS);
	पूर्ण
	ग_लिखो_csr(dd, ASIC_CFG_SBUS_EXECUTE, 0);
पूर्ण

पूर्णांक load_firmware(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	अगर (fw_fabric_serdes_load) अणु
		ret = acquire_chip_resource(dd, CR_SBUS, SBUS_TIMEOUT);
		अगर (ret)
			वापस ret;

		set_sbus_fast_mode(dd);

		set_serdes_broadcast(dd, all_fabric_serdes_broadcast,
				     fabric_serdes_broadcast[dd->hfi1_id],
				     fabric_serdes_addrs[dd->hfi1_id],
				     NUM_FABRIC_SERDES);
		turn_off_spicos(dd, SPICO_FABRIC);
		करो अणु
			ret = load_fabric_serdes_firmware(dd, &fw_fabric);
		पूर्ण जबतक (retry_firmware(dd, ret));

		clear_sbus_fast_mode(dd);
		release_chip_resource(dd, CR_SBUS);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (fw_8051_load) अणु
		करो अणु
			ret = load_8051_firmware(dd, &fw_8051);
		पूर्ण जबतक (retry_firmware(dd, ret));
		अगर (ret)
			वापस ret;
	पूर्ण

	dump_fw_version(dd);
	वापस 0;
पूर्ण

पूर्णांक hfi1_firmware_init(काष्ठा hfi1_devdata *dd)
अणु
	/* only RTL can use these */
	अगर (dd->icode != ICODE_RTL_SILICON) अणु
		fw_fabric_serdes_load = 0;
		fw_pcie_serdes_load = 0;
		fw_sbus_load = 0;
	पूर्ण

	/* no 8051 or QSFP on simulator */
	अगर (dd->icode == ICODE_FUNCTIONAL_SIMULATOR)
		fw_8051_load = 0;

	अगर (!fw_8051_name) अणु
		अगर (dd->icode == ICODE_RTL_SILICON)
			fw_8051_name = DEFAULT_FW_8051_NAME_ASIC;
		अन्यथा
			fw_8051_name = DEFAULT_FW_8051_NAME_FPGA;
	पूर्ण
	अगर (!fw_fabric_serdes_name)
		fw_fabric_serdes_name = DEFAULT_FW_FABRIC_NAME;
	अगर (!fw_sbus_name)
		fw_sbus_name = DEFAULT_FW_SBUS_NAME;
	अगर (!fw_pcie_serdes_name)
		fw_pcie_serdes_name = DEFAULT_FW_PCIE_NAME;

	वापस obtain_firmware(dd);
पूर्ण

/*
 * This function is a helper function क्रम parse_platक्रमm_config(...) and
 * करोes not check क्रम validity of the platक्रमm configuration cache
 * (because we know it is invalid as we are building up the cache).
 * As such, this should not be called from anywhere other than
 * parse_platक्रमm_config
 */
अटल पूर्णांक check_meta_version(काष्ठा hfi1_devdata *dd, u32 *प्रणाली_table)
अणु
	u32 meta_ver, meta_ver_meta, ver_start, ver_len, mask;
	काष्ठा platक्रमm_config_cache *pcfgcache = &dd->pcfg_cache;

	अगर (!प्रणाली_table)
		वापस -EINVAL;

	meta_ver_meta =
	*(pcfgcache->config_tables[PLATFORM_CONFIG_SYSTEM_TABLE].table_metadata
	+ SYSTEM_TABLE_META_VERSION);

	mask = ((1 << METADATA_TABLE_FIELD_START_LEN_BITS) - 1);
	ver_start = meta_ver_meta & mask;

	meta_ver_meta >>= METADATA_TABLE_FIELD_LEN_SHIFT;

	mask = ((1 << METADATA_TABLE_FIELD_LEN_LEN_BITS) - 1);
	ver_len = meta_ver_meta & mask;

	ver_start /= 8;
	meta_ver = *((u8 *)प्रणाली_table + ver_start) & ((1 << ver_len) - 1);

	अगर (meta_ver < 4) अणु
		dd_dev_info(
			dd, "%s:Please update platform config\n", __func__);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक parse_platक्रमm_config(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा platक्रमm_config_cache *pcfgcache = &dd->pcfg_cache;
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	u32 *ptr = शून्य;
	u32 header1 = 0, header2 = 0, magic_num = 0, crc = 0, file_length = 0;
	u32 record_idx = 0, table_type = 0, table_length_dwords = 0;
	पूर्णांक ret = -EINVAL; /* assume failure */

	/*
	 * For पूर्णांकegrated devices that did not fall back to the शेष file,
	 * the SI tuning inक्रमmation क्रम active channels is acquired from the
	 * scratch रेजिस्टर biपंचांगap, thus there is no platक्रमm config to parse.
	 * Skip parsing in these situations.
	 */
	अगर (ppd->config_from_scratch)
		वापस 0;

	अगर (!dd->platक्रमm_config.data) अणु
		dd_dev_err(dd, "%s: Missing config file\n", __func__);
		जाओ bail;
	पूर्ण
	ptr = (u32 *)dd->platक्रमm_config.data;

	magic_num = *ptr;
	ptr++;
	अगर (magic_num != PLATFORM_CONFIG_MAGIC_NUM) अणु
		dd_dev_err(dd, "%s: Bad config file\n", __func__);
		जाओ bail;
	पूर्ण

	/* Field is file size in DWORDs */
	file_length = (*ptr) * 4;

	/*
	 * Length can't be larger than partition size. Assume platक्रमm
	 * config क्रमmat version 4 is being used. Interpret the file size
	 * field as header instead by not moving the poपूर्णांकer.
	 */
	अगर (file_length > MAX_PLATFORM_CONFIG_खाता_SIZE) अणु
		dd_dev_info(dd,
			    "%s:File length out of bounds, using alternative format\n",
			    __func__);
		file_length = PLATFORM_CONFIG_FORMAT_4_खाता_SIZE;
	पूर्ण अन्यथा अणु
		ptr++;
	पूर्ण

	अगर (file_length > dd->platक्रमm_config.size) अणु
		dd_dev_info(dd, "%s:File claims to be larger than read size\n",
			    __func__);
		जाओ bail;
	पूर्ण अन्यथा अगर (file_length < dd->platक्रमm_config.size) अणु
		dd_dev_info(dd,
			    "%s:File claims to be smaller than read size, continuing\n",
			    __func__);
	पूर्ण
	/* exactly equal, perfection */

	/*
	 * In both हालs where we proceed, using the self-reported file length
	 * is the safer option. In हाल of old क्रमmat a predefined value is
	 * being used.
	 */
	जबतक (ptr < (u32 *)(dd->platक्रमm_config.data + file_length)) अणु
		header1 = *ptr;
		header2 = *(ptr + 1);
		अगर (header1 != ~header2) अणु
			dd_dev_err(dd, "%s: Failed validation at offset %ld\n",
				   __func__, (ptr - (u32 *)
					      dd->platक्रमm_config.data));
			जाओ bail;
		पूर्ण

		record_idx = *ptr &
			((1 << PLATFORM_CONFIG_HEADER_RECORD_IDX_LEN_BITS) - 1);

		table_length_dwords = (*ptr >>
				PLATFORM_CONFIG_HEADER_TABLE_LENGTH_SHIFT) &
		      ((1 << PLATFORM_CONFIG_HEADER_TABLE_LENGTH_LEN_BITS) - 1);

		table_type = (*ptr >> PLATFORM_CONFIG_HEADER_TABLE_TYPE_SHIFT) &
			((1 << PLATFORM_CONFIG_HEADER_TABLE_TYPE_LEN_BITS) - 1);

		/* Done with this set of headers */
		ptr += 2;

		अगर (record_idx) अणु
			/* data table */
			चयन (table_type) अणु
			हाल PLATFORM_CONFIG_SYSTEM_TABLE:
				pcfgcache->config_tables[table_type].num_table =
									1;
				ret = check_meta_version(dd, ptr);
				अगर (ret)
					जाओ bail;
				अवरोध;
			हाल PLATFORM_CONFIG_PORT_TABLE:
				pcfgcache->config_tables[table_type].num_table =
									2;
				अवरोध;
			हाल PLATFORM_CONFIG_RX_PRESET_TABLE:
			हाल PLATFORM_CONFIG_TX_PRESET_TABLE:
			हाल PLATFORM_CONFIG_QSFP_ATTEN_TABLE:
			हाल PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE:
				pcfgcache->config_tables[table_type].num_table =
							table_length_dwords;
				अवरोध;
			शेष:
				dd_dev_err(dd,
					   "%s: Unknown data table %d, offset %ld\n",
					   __func__, table_type,
					   (ptr - (u32 *)
					    dd->platक्रमm_config.data));
				जाओ bail; /* We करोn't trust this file now */
			पूर्ण
			pcfgcache->config_tables[table_type].table = ptr;
		पूर्ण अन्यथा अणु
			/* metadata table */
			चयन (table_type) अणु
			हाल PLATFORM_CONFIG_SYSTEM_TABLE:
			हाल PLATFORM_CONFIG_PORT_TABLE:
			हाल PLATFORM_CONFIG_RX_PRESET_TABLE:
			हाल PLATFORM_CONFIG_TX_PRESET_TABLE:
			हाल PLATFORM_CONFIG_QSFP_ATTEN_TABLE:
			हाल PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE:
				अवरोध;
			शेष:
				dd_dev_err(dd,
					   "%s: Unknown meta table %d, offset %ld\n",
					   __func__, table_type,
					   (ptr -
					    (u32 *)dd->platक्रमm_config.data));
				जाओ bail; /* We करोn't trust this file now */
			पूर्ण
			pcfgcache->config_tables[table_type].table_metadata =
									ptr;
		पूर्ण

		/* Calculate and check table crc */
		crc = crc32_le(~(u32)0, (अचिन्हित अक्षर स्थिर *)ptr,
			       (table_length_dwords * 4));
		crc ^= ~(u32)0;

		/* Jump the table */
		ptr += table_length_dwords;
		अगर (crc != *ptr) अणु
			dd_dev_err(dd, "%s: Failed CRC check at offset %ld\n",
				   __func__, (ptr -
				   (u32 *)dd->platक्रमm_config.data));
			ret = -EINVAL;
			जाओ bail;
		पूर्ण
		/* Jump the CRC DWORD */
		ptr++;
	पूर्ण

	pcfgcache->cache_valid = 1;
	वापस 0;
bail:
	स_रखो(pcfgcache, 0, माप(काष्ठा platक्रमm_config_cache));
	वापस ret;
पूर्ण

अटल व्योम get_पूर्णांकegrated_platक्रमm_config_field(
		काष्ठा hfi1_devdata *dd,
		क्रमागत platक्रमm_config_table_type_encoding table_type,
		पूर्णांक field_index, u32 *data)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	u8 *cache = ppd->qsfp_info.cache;
	u32 tx_preset = 0;

	चयन (table_type) अणु
	हाल PLATFORM_CONFIG_SYSTEM_TABLE:
		अगर (field_index == SYSTEM_TABLE_QSFP_POWER_CLASS_MAX)
			*data = ppd->max_घातer_class;
		अन्यथा अगर (field_index == SYSTEM_TABLE_QSFP_ATTENUATION_DEFAULT_25G)
			*data = ppd->शेष_atten;
		अवरोध;
	हाल PLATFORM_CONFIG_PORT_TABLE:
		अगर (field_index == PORT_TABLE_PORT_TYPE)
			*data = ppd->port_type;
		अन्यथा अगर (field_index == PORT_TABLE_LOCAL_ATTEN_25G)
			*data = ppd->local_atten;
		अन्यथा अगर (field_index == PORT_TABLE_REMOTE_ATTEN_25G)
			*data = ppd->remote_atten;
		अवरोध;
	हाल PLATFORM_CONFIG_RX_PRESET_TABLE:
		अगर (field_index == RX_PRESET_TABLE_QSFP_RX_CDR_APPLY)
			*data = (ppd->rx_preset & QSFP_RX_CDR_APPLY_SMASK) >>
				QSFP_RX_CDR_APPLY_SHIFT;
		अन्यथा अगर (field_index == RX_PRESET_TABLE_QSFP_RX_EMP_APPLY)
			*data = (ppd->rx_preset & QSFP_RX_EMP_APPLY_SMASK) >>
				QSFP_RX_EMP_APPLY_SHIFT;
		अन्यथा अगर (field_index == RX_PRESET_TABLE_QSFP_RX_AMP_APPLY)
			*data = (ppd->rx_preset & QSFP_RX_AMP_APPLY_SMASK) >>
				QSFP_RX_AMP_APPLY_SHIFT;
		अन्यथा अगर (field_index == RX_PRESET_TABLE_QSFP_RX_CDR)
			*data = (ppd->rx_preset & QSFP_RX_CDR_SMASK) >>
				QSFP_RX_CDR_SHIFT;
		अन्यथा अगर (field_index == RX_PRESET_TABLE_QSFP_RX_EMP)
			*data = (ppd->rx_preset & QSFP_RX_EMP_SMASK) >>
				QSFP_RX_EMP_SHIFT;
		अन्यथा अगर (field_index == RX_PRESET_TABLE_QSFP_RX_AMP)
			*data = (ppd->rx_preset & QSFP_RX_AMP_SMASK) >>
				QSFP_RX_AMP_SHIFT;
		अवरोध;
	हाल PLATFORM_CONFIG_TX_PRESET_TABLE:
		अगर (cache[QSFP_EQ_INFO_OFFS] & 0x4)
			tx_preset = ppd->tx_preset_eq;
		अन्यथा
			tx_preset = ppd->tx_preset_noeq;
		अगर (field_index == TX_PRESET_TABLE_PRECUR)
			*data = (tx_preset & TX_PRECUR_SMASK) >>
				TX_PRECUR_SHIFT;
		अन्यथा अगर (field_index == TX_PRESET_TABLE_ATTN)
			*data = (tx_preset & TX_ATTN_SMASK) >>
				TX_ATTN_SHIFT;
		अन्यथा अगर (field_index == TX_PRESET_TABLE_POSTCUR)
			*data = (tx_preset & TX_POSTCUR_SMASK) >>
				TX_POSTCUR_SHIFT;
		अन्यथा अगर (field_index == TX_PRESET_TABLE_QSFP_TX_CDR_APPLY)
			*data = (tx_preset & QSFP_TX_CDR_APPLY_SMASK) >>
				QSFP_TX_CDR_APPLY_SHIFT;
		अन्यथा अगर (field_index == TX_PRESET_TABLE_QSFP_TX_EQ_APPLY)
			*data = (tx_preset & QSFP_TX_EQ_APPLY_SMASK) >>
				QSFP_TX_EQ_APPLY_SHIFT;
		अन्यथा अगर (field_index == TX_PRESET_TABLE_QSFP_TX_CDR)
			*data = (tx_preset & QSFP_TX_CDR_SMASK) >>
				QSFP_TX_CDR_SHIFT;
		अन्यथा अगर (field_index == TX_PRESET_TABLE_QSFP_TX_EQ)
			*data = (tx_preset & QSFP_TX_EQ_SMASK) >>
				QSFP_TX_EQ_SHIFT;
		अवरोध;
	हाल PLATFORM_CONFIG_QSFP_ATTEN_TABLE:
	हाल PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक get_platक्रमm_fw_field_metadata(काष्ठा hfi1_devdata *dd, पूर्णांक table,
					  पूर्णांक field, u32 *field_len_bits,
					  u32 *field_start_bits)
अणु
	काष्ठा platक्रमm_config_cache *pcfgcache = &dd->pcfg_cache;
	u32 *src_ptr = शून्य;

	अगर (!pcfgcache->cache_valid)
		वापस -EINVAL;

	चयन (table) अणु
	हाल PLATFORM_CONFIG_SYSTEM_TABLE:
	हाल PLATFORM_CONFIG_PORT_TABLE:
	हाल PLATFORM_CONFIG_RX_PRESET_TABLE:
	हाल PLATFORM_CONFIG_TX_PRESET_TABLE:
	हाल PLATFORM_CONFIG_QSFP_ATTEN_TABLE:
	हाल PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE:
		अगर (field && field < platक्रमm_config_table_limits[table])
			src_ptr =
			pcfgcache->config_tables[table].table_metadata + field;
		अवरोध;
	शेष:
		dd_dev_info(dd, "%s: Unknown table\n", __func__);
		अवरोध;
	पूर्ण

	अगर (!src_ptr)
		वापस -EINVAL;

	अगर (field_start_bits)
		*field_start_bits = *src_ptr &
		      ((1 << METADATA_TABLE_FIELD_START_LEN_BITS) - 1);

	अगर (field_len_bits)
		*field_len_bits = (*src_ptr >> METADATA_TABLE_FIELD_LEN_SHIFT)
		       & ((1 << METADATA_TABLE_FIELD_LEN_LEN_BITS) - 1);

	वापस 0;
पूर्ण

/* This is the central पूर्णांकerface to getting data out of the platक्रमm config
 * file. It depends on parse_platक्रमm_config() having populated the
 * platक्रमm_config_cache in hfi1_devdata, and checks the cache_valid member to
 * validate the sanity of the cache.
 *
 * The non-obvious parameters:
 * @table_index: Acts as a look up key पूर्णांकo which instance of the tables the
 * relevant field is fetched from.
 *
 * This applies to the data tables that have multiple instances. The port table
 * is an exception to this rule as each HFI only has one port and thus the
 * relevant table can be distinguished by hfi_id.
 *
 * @data: poपूर्णांकer to memory that will be populated with the field requested.
 * @len: length of memory poपूर्णांकed by @data in bytes.
 */
पूर्णांक get_platक्रमm_config_field(काष्ठा hfi1_devdata *dd,
			      क्रमागत platक्रमm_config_table_type_encoding
			      table_type, पूर्णांक table_index, पूर्णांक field_index,
			      u32 *data, u32 len)
अणु
	पूर्णांक ret = 0, wlen = 0, seek = 0;
	u32 field_len_bits = 0, field_start_bits = 0, *src_ptr = शून्य;
	काष्ठा platक्रमm_config_cache *pcfgcache = &dd->pcfg_cache;
	काष्ठा hfi1_pportdata *ppd = dd->pport;

	अगर (data)
		स_रखो(data, 0, len);
	अन्यथा
		वापस -EINVAL;

	अगर (ppd->config_from_scratch) अणु
		/*
		 * Use saved configuration from ppd क्रम पूर्णांकegrated platक्रमms
		 */
		get_पूर्णांकegrated_platक्रमm_config_field(dd, table_type,
						     field_index, data);
		वापस 0;
	पूर्ण

	ret = get_platक्रमm_fw_field_metadata(dd, table_type, field_index,
					     &field_len_bits,
					     &field_start_bits);
	अगर (ret)
		वापस -EINVAL;

	/* Convert length to bits */
	len *= 8;

	/* Our metadata function checked cache_valid and field_index क्रम us */
	चयन (table_type) अणु
	हाल PLATFORM_CONFIG_SYSTEM_TABLE:
		src_ptr = pcfgcache->config_tables[table_type].table;

		अगर (field_index != SYSTEM_TABLE_QSFP_POWER_CLASS_MAX) अणु
			अगर (len < field_len_bits)
				वापस -EINVAL;

			seek = field_start_bits / 8;
			wlen = field_len_bits / 8;

			src_ptr = (u32 *)((u8 *)src_ptr + seek);

			/*
			 * We expect the field to be byte aligned and whole byte
			 * lengths अगर we are here
			 */
			स_नकल(data, src_ptr, wlen);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल PLATFORM_CONFIG_PORT_TABLE:
		/* Port table is 4 DWORDS */
		src_ptr = dd->hfi1_id ?
			pcfgcache->config_tables[table_type].table + 4 :
			pcfgcache->config_tables[table_type].table;
		अवरोध;
	हाल PLATFORM_CONFIG_RX_PRESET_TABLE:
	हाल PLATFORM_CONFIG_TX_PRESET_TABLE:
	हाल PLATFORM_CONFIG_QSFP_ATTEN_TABLE:
	हाल PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE:
		src_ptr = pcfgcache->config_tables[table_type].table;

		अगर (table_index <
			pcfgcache->config_tables[table_type].num_table)
			src_ptr += table_index;
		अन्यथा
			src_ptr = शून्य;
		अवरोध;
	शेष:
		dd_dev_info(dd, "%s: Unknown table\n", __func__);
		अवरोध;
	पूर्ण

	अगर (!src_ptr || len < field_len_bits)
		वापस -EINVAL;

	src_ptr += (field_start_bits / 32);
	*data = (*src_ptr >> (field_start_bits % 32)) &
			((1 << field_len_bits) - 1);

	वापस 0;
पूर्ण

/*
 * Download the firmware needed क्रम the Gen3 PCIe SerDes.  An update
 * to the SBus firmware is needed beक्रमe updating the PCIe firmware.
 *
 * Note: caller must be holding the SBus resource.
 */
पूर्णांक load_pcie_firmware(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret = 0;

	/* both firmware loads below use the SBus */
	set_sbus_fast_mode(dd);

	अगर (fw_sbus_load) अणु
		turn_off_spicos(dd, SPICO_SBUS);
		करो अणु
			ret = load_sbus_firmware(dd, &fw_sbus);
		पूर्ण जबतक (retry_firmware(dd, ret));
		अगर (ret)
			जाओ करोne;
	पूर्ण

	अगर (fw_pcie_serdes_load) अणु
		dd_dev_info(dd, "Setting PCIe SerDes broadcast\n");
		set_serdes_broadcast(dd, all_pcie_serdes_broadcast,
				     pcie_serdes_broadcast[dd->hfi1_id],
				     pcie_serdes_addrs[dd->hfi1_id],
				     NUM_PCIE_SERDES);
		करो अणु
			ret = load_pcie_serdes_firmware(dd, &fw_pcie);
		पूर्ण जबतक (retry_firmware(dd, ret));
		अगर (ret)
			जाओ करोne;
	पूर्ण

करोne:
	clear_sbus_fast_mode(dd);

	वापस ret;
पूर्ण

/*
 * Read the GUID from the hardware, store it in dd.
 */
व्योम पढ़ो_guid(काष्ठा hfi1_devdata *dd)
अणु
	/* Take the DC out of reset to get a valid GUID value */
	ग_लिखो_csr(dd, CCE_DC_CTRL, 0);
	(व्योम)पढ़ो_csr(dd, CCE_DC_CTRL);

	dd->base_guid = पढ़ो_csr(dd, DC_DC8051_CFG_LOCAL_GUID);
	dd_dev_info(dd, "GUID %llx",
		    (अचिन्हित दीर्घ दीर्घ)dd->base_guid);
पूर्ण

/* पढ़ो and display firmware version info */
अटल व्योम dump_fw_version(काष्ठा hfi1_devdata *dd)
अणु
	u32 pcie_vers[NUM_PCIE_SERDES];
	u32 fabric_vers[NUM_FABRIC_SERDES];
	u32 sbus_vers;
	पूर्णांक i;
	पूर्णांक all_same;
	पूर्णांक ret;
	u8 rcv_addr;

	ret = acquire_chip_resource(dd, CR_SBUS, SBUS_TIMEOUT);
	अगर (ret) अणु
		dd_dev_err(dd, "Unable to acquire SBus to read firmware versions\n");
		वापस;
	पूर्ण

	/* set fast mode */
	set_sbus_fast_mode(dd);

	/* पढ़ो version क्रम SBus Master */
	sbus_request(dd, SBUS_MASTER_BROADCAST, 0x02, WRITE_SBUS_RECEIVER, 0);
	sbus_request(dd, SBUS_MASTER_BROADCAST, 0x07, WRITE_SBUS_RECEIVER, 0x1);
	/* रुको क्रम पूर्णांकerrupt to be processed */
	usleep_range(10000, 11000);
	sbus_vers = sbus_पढ़ो(dd, SBUS_MASTER_BROADCAST, 0x08, 0x1);
	dd_dev_info(dd, "SBus Master firmware version 0x%08x\n", sbus_vers);

	/* पढ़ो version क्रम PCIe SerDes */
	all_same = 1;
	pcie_vers[0] = 0;
	क्रम (i = 0; i < NUM_PCIE_SERDES; i++) अणु
		rcv_addr = pcie_serdes_addrs[dd->hfi1_id][i];
		sbus_request(dd, rcv_addr, 0x03, WRITE_SBUS_RECEIVER, 0);
		/* रुको क्रम पूर्णांकerrupt to be processed */
		usleep_range(10000, 11000);
		pcie_vers[i] = sbus_पढ़ो(dd, rcv_addr, 0x04, 0x0);
		अगर (i > 0 && pcie_vers[0] != pcie_vers[i])
			all_same = 0;
	पूर्ण

	अगर (all_same) अणु
		dd_dev_info(dd, "PCIe SerDes firmware version 0x%x\n",
			    pcie_vers[0]);
	पूर्ण अन्यथा अणु
		dd_dev_warn(dd, "PCIe SerDes do not have the same firmware version\n");
		क्रम (i = 0; i < NUM_PCIE_SERDES; i++) अणु
			dd_dev_info(dd,
				    "PCIe SerDes lane %d firmware version 0x%x\n",
				    i, pcie_vers[i]);
		पूर्ण
	पूर्ण

	/* पढ़ो version क्रम fabric SerDes */
	all_same = 1;
	fabric_vers[0] = 0;
	क्रम (i = 0; i < NUM_FABRIC_SERDES; i++) अणु
		rcv_addr = fabric_serdes_addrs[dd->hfi1_id][i];
		sbus_request(dd, rcv_addr, 0x03, WRITE_SBUS_RECEIVER, 0);
		/* रुको क्रम पूर्णांकerrupt to be processed */
		usleep_range(10000, 11000);
		fabric_vers[i] = sbus_पढ़ो(dd, rcv_addr, 0x04, 0x0);
		अगर (i > 0 && fabric_vers[0] != fabric_vers[i])
			all_same = 0;
	पूर्ण

	अगर (all_same) अणु
		dd_dev_info(dd, "Fabric SerDes firmware version 0x%x\n",
			    fabric_vers[0]);
	पूर्ण अन्यथा अणु
		dd_dev_warn(dd, "Fabric SerDes do not have the same firmware version\n");
		क्रम (i = 0; i < NUM_FABRIC_SERDES; i++) अणु
			dd_dev_info(dd,
				    "Fabric SerDes lane %d firmware version 0x%x\n",
				    i, fabric_vers[i]);
		पूर्ण
	पूर्ण

	clear_sbus_fast_mode(dd);
	release_chip_resource(dd, CR_SBUS);
पूर्ण
