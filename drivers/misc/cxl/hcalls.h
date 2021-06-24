<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2015 IBM Corp.
 */

#अगर_अघोषित _HCALLS_H
#घोषणा _HCALLS_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/hvcall.h>
#समावेश "cxl.h"

#घोषणा SG_BUFFER_SIZE 4096
#घोषणा SG_MAX_ENTRIES 256

काष्ठा sg_list अणु
	u64 phys_addr;
	u64 len;
पूर्ण;

/*
 * This is straight out of PAPR, but replacing some of the compound fields with
 * a single field, where they were identical to the रेजिस्टर layout.
 *
 * The 'flags' parameter regroups the various bit-fields
 */
#घोषणा CXL_PE_CSRP_VALID			(1ULL << 63)
#घोषणा CXL_PE_PROBLEM_STATE			(1ULL << 62)
#घोषणा CXL_PE_SECONDARY_SEGMENT_TBL_SRCH	(1ULL << 61)
#घोषणा CXL_PE_TAGS_ACTIVE			(1ULL << 60)
#घोषणा CXL_PE_USER_STATE			(1ULL << 59)
#घोषणा CXL_PE_TRANSLATION_ENABLED		(1ULL << 58)
#घोषणा CXL_PE_64_BIT				(1ULL << 57)
#घोषणा CXL_PE_PRIVILEGED_PROCESS		(1ULL << 56)

#घोषणा CXL_PROCESS_ELEMENT_VERSION 1
काष्ठा cxl_process_element_hcall अणु
	__be64 version;
	__be64 flags;
	u8     reserved0[12];
	__be32 pslVirtualIsn;
	u8     applicationVirtualIsnBiपंचांगap[256];
	u8     reserved1[144];
	काष्ठा cxl_process_element_common common;
	u8     reserved4[12];
पूर्ण __packed;

#घोषणा H_STATE_NORMAL              1
#घोषणा H_STATE_DISABLE             2
#घोषणा H_STATE_TEMP_UNAVAILABLE    3
#घोषणा H_STATE_PERM_UNAVAILABLE    4

/* NOTE: element must be a logical real address, and must be pinned */
दीर्घ cxl_h_attach_process(u64 unit_address, काष्ठा cxl_process_element_hcall *element,
			u64 *process_token, u64 *mmio_addr, u64 *mmio_size);

/**
 * cxl_h_detach_process - Detach a process element from a coherent
 *                        platक्रमm function.
 */
दीर्घ cxl_h_detach_process(u64 unit_address, u64 process_token);

/**
 * cxl_h_reset_afu - Perक्रमm a reset to the coherent platक्रमm function.
 */
दीर्घ cxl_h_reset_afu(u64 unit_address);

/**
 * cxl_h_suspend_process - Suspend a process from being executed
 * Parameter1 = process-token as वापसed from H_ATTACH_CA_PROCESS when
 *              process was attached.
 */
दीर्घ cxl_h_suspend_process(u64 unit_address, u64 process_token);

/**
 * cxl_h_resume_process - Resume a process to be executed
 * Parameter1 = process-token as वापसed from H_ATTACH_CA_PROCESS when
 *              process was attached.
 */
दीर्घ cxl_h_resume_process(u64 unit_address, u64 process_token);

/**
 * cxl_h_पढ़ो_error_state - Reads the error state of the coherent
 *                          platक्रमm function.
 * R4 contains the error state
 */
दीर्घ cxl_h_पढ़ो_error_state(u64 unit_address, u64 *state);

/**
 * cxl_h_get_afu_err - collect the AFU error buffer
 * Parameter1 = byte offset पूर्णांकo error buffer to retrieve, valid values
 *              are between 0 and (ibm,error-buffer-size - 1)
 * Parameter2 = 4K aligned real address of error buffer, to be filled in
 * Parameter3 = length of error buffer, valid values are 4K or less
 */
दीर्घ cxl_h_get_afu_err(u64 unit_address, u64 offset, u64 buf_address, u64 len);

/**
 * cxl_h_get_config - collect configuration record क्रम the
 *                    coherent platक्रमm function
 * Parameter1 = # of configuration record to retrieve, valid values are
 *              between 0 and (ibm,#config-records - 1)
 * Parameter2 = byte offset पूर्णांकo configuration record to retrieve,
 *              valid values are between 0 and (ibm,config-record-size - 1)
 * Parameter3 = 4K aligned real address of configuration record buffer,
 *              to be filled in
 * Parameter4 = length of configuration buffer, valid values are 4K or less
 */
दीर्घ cxl_h_get_config(u64 unit_address, u64 cr_num, u64 offset,
		u64 buf_address, u64 len);

/**
 * cxl_h_terminate_process - Terminate the process beक्रमe completion
 * Parameter1 = process-token as वापसed from H_ATTACH_CA_PROCESS when
 *              process was attached.
 */
दीर्घ cxl_h_terminate_process(u64 unit_address, u64 process_token);

/**
 * cxl_h_collect_vpd - Collect VPD क्रम the coherent platक्रमm function.
 * Parameter1 = # of VPD record to retrieve, valid values are between 0
 *              and (ibm,#config-records - 1).
 * Parameter2 = 4K naturally aligned real buffer containing block
 *              list entries
 * Parameter3 = number of block list entries in the block list, valid
 *              values are between 0 and 256
 */
दीर्घ cxl_h_collect_vpd(u64 unit_address, u64 record, u64 list_address,
		       u64 num, u64 *out);

/**
 * cxl_h_get_fn_error_पूर्णांकerrupt - Read the function-wide error data based on an पूर्णांकerrupt
 */
दीर्घ cxl_h_get_fn_error_पूर्णांकerrupt(u64 unit_address, u64 *reg);

/**
 * cxl_h_ack_fn_error_पूर्णांकerrupt - Acknowledge function-wide error data
 *                                based on an पूर्णांकerrupt
 * Parameter1 = value to ग_लिखो to the function-wide error पूर्णांकerrupt रेजिस्टर
 */
दीर्घ cxl_h_ack_fn_error_पूर्णांकerrupt(u64 unit_address, u64 value);

/**
 * cxl_h_get_error_log - Retrieve the Platक्रमm Log ID (PLID) of
 *                       an error log
 */
दीर्घ cxl_h_get_error_log(u64 unit_address, u64 value);

/**
 * cxl_h_collect_पूर्णांक_info - Collect पूर्णांकerrupt info about a coherent
 *                          platक्रमm function after an पूर्णांकerrupt occurred.
 */
दीर्घ cxl_h_collect_पूर्णांक_info(u64 unit_address, u64 process_token,
			काष्ठा cxl_irq_info *info);

/**
 * cxl_h_control_faults - Control the operation of a coherent platक्रमm
 *                        function after a fault occurs.
 *
 * Parameters
 *    control-mask: value to control the faults
 *                  looks like PSL_TFC_An shअगरted >> 32
 *    reset-mask: mask to control reset of function faults
 *                Set reset_mask = 1 to reset PSL errors
 */
दीर्घ cxl_h_control_faults(u64 unit_address, u64 process_token,
			u64 control_mask, u64 reset_mask);

/**
 * cxl_h_reset_adapter - Perक्रमm a reset to the coherent platक्रमm facility.
 */
दीर्घ cxl_h_reset_adapter(u64 unit_address);

/**
 * cxl_h_collect_vpd - Collect VPD क्रम the coherent platक्रमm function.
 * Parameter1 = 4K naturally aligned real buffer containing block
 *              list entries
 * Parameter2 = number of block list entries in the block list, valid
 *              values are between 0 and 256
 */
दीर्घ cxl_h_collect_vpd_adapter(u64 unit_address, u64 list_address,
			       u64 num, u64 *out);

/**
 * cxl_h_करोwnload_adapter_image - Download the base image to the coherent
 *                                platक्रमm facility.
 */
दीर्घ cxl_h_करोwnload_adapter_image(u64 unit_address,
				  u64 list_address, u64 num,
				  u64 *out);

/**
 * cxl_h_validate_adapter_image - Validate the base image in the coherent
 *                                platक्रमm facility.
 */
दीर्घ cxl_h_validate_adapter_image(u64 unit_address,
				  u64 list_address, u64 num,
				  u64 *out);
#पूर्ण_अगर /* _HCALLS_H */
