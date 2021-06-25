<शैली गुरु>
/******************************************************************************
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2019 - 2020 Intel Corporation
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
 * The full GNU General Public License is included in this distribution
 * in the file called COPYING.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 * BSD LICENSE
 *
 * Copyright(c) 2019 - 2020 Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name Intel Corporation nor the names of its
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
 *****************************************************************************/

#समावेश "img.h"

u8 iwl_fw_lookup_cmd_ver(स्थिर काष्ठा iwl_fw *fw, u8 grp, u8 cmd, u8 def)
अणु
	स्थिर काष्ठा iwl_fw_cmd_version *entry;
	अचिन्हित पूर्णांक i;

	अगर (!fw->ucode_capa.cmd_versions ||
	    !fw->ucode_capa.n_cmd_versions)
		वापस def;

	entry = fw->ucode_capa.cmd_versions;
	क्रम (i = 0; i < fw->ucode_capa.n_cmd_versions; i++, entry++) अणु
		अगर (entry->group == grp && entry->cmd == cmd) अणु
			अगर (entry->cmd_ver == IWL_FW_CMD_VER_UNKNOWN)
				वापस def;
			वापस entry->cmd_ver;
		पूर्ण
	पूर्ण

	वापस def;
पूर्ण
EXPORT_SYMBOL_GPL(iwl_fw_lookup_cmd_ver);

u8 iwl_fw_lookup_notअगर_ver(स्थिर काष्ठा iwl_fw *fw, u8 grp, u8 cmd, u8 def)
अणु
	स्थिर काष्ठा iwl_fw_cmd_version *entry;
	अचिन्हित पूर्णांक i;

	अगर (!fw->ucode_capa.cmd_versions ||
	    !fw->ucode_capa.n_cmd_versions)
		वापस def;

	entry = fw->ucode_capa.cmd_versions;
	क्रम (i = 0; i < fw->ucode_capa.n_cmd_versions; i++, entry++) अणु
		अगर (entry->group == grp && entry->cmd == cmd) अणु
			अगर (entry->notअगर_ver == IWL_FW_CMD_VER_UNKNOWN)
				वापस def;
			वापस entry->notअगर_ver;
		पूर्ण
	पूर्ण

	वापस def;
पूर्ण
EXPORT_SYMBOL_GPL(iwl_fw_lookup_notअगर_ver);

#घोषणा FW_SYSASSERT_CPU_MASK 0xf0000000
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	u8 num;
पूर्ण advanced_lookup[] = अणु
	अणु "NMI_INTERRUPT_WDG", 0x34 पूर्ण,
	अणु "SYSASSERT", 0x35 पूर्ण,
	अणु "UCODE_VERSION_MISMATCH", 0x37 पूर्ण,
	अणु "BAD_COMMAND", 0x38 पूर्ण,
	अणु "BAD_COMMAND", 0x39 पूर्ण,
	अणु "NMI_INTERRUPT_DATA_ACTION_PT", 0x3C पूर्ण,
	अणु "FATAL_ERROR", 0x3D पूर्ण,
	अणु "NMI_TRM_HW_ERR", 0x46 पूर्ण,
	अणु "NMI_INTERRUPT_TRM", 0x4C पूर्ण,
	अणु "NMI_INTERRUPT_BREAK_POINT", 0x54 पूर्ण,
	अणु "NMI_INTERRUPT_WDG_RXF_FULL", 0x5C पूर्ण,
	अणु "NMI_INTERRUPT_WDG_NO_RBD_RXF_FULL", 0x64 पूर्ण,
	अणु "NMI_INTERRUPT_HOST", 0x66 पूर्ण,
	अणु "NMI_INTERRUPT_LMAC_FATAL", 0x70 पूर्ण,
	अणु "NMI_INTERRUPT_UMAC_FATAL", 0x71 पूर्ण,
	अणु "NMI_INTERRUPT_OTHER_LMAC_FATAL", 0x73 पूर्ण,
	अणु "NMI_INTERRUPT_ACTION_PT", 0x7C पूर्ण,
	अणु "NMI_INTERRUPT_UNKNOWN", 0x84 पूर्ण,
	अणु "NMI_INTERRUPT_INST_ACTION_PT", 0x86 पूर्ण,
	अणु "ADVANCED_SYSASSERT", 0 पूर्ण,
पूर्ण;

स्थिर अक्षर *iwl_fw_lookup_निश्चित_desc(u32 num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(advanced_lookup) - 1; i++)
		अगर (advanced_lookup[i].num == (num & ~FW_SYSASSERT_CPU_MASK))
			वापस advanced_lookup[i].name;

	/* No entry matches 'num', so it is the last: ADVANCED_SYSASSERT */
	वापस advanced_lookup[i].name;
पूर्ण
EXPORT_SYMBOL_GPL(iwl_fw_lookup_निश्चित_desc);
