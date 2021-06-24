<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 IBM Corp.
 */


#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "hcalls.h"
#समावेश "trace.h"

#घोषणा CXL_HCALL_TIMEOUT 60000
#घोषणा CXL_HCALL_TIMEOUT_DOWNLOAD 120000

#घोषणा H_ATTACH_CA_PROCESS    0x344
#घोषणा H_CONTROL_CA_FUNCTION  0x348
#घोषणा H_DETACH_CA_PROCESS    0x34C
#घोषणा H_COLLECT_CA_INT_INFO  0x350
#घोषणा H_CONTROL_CA_FAULTS    0x354
#घोषणा H_DOWNLOAD_CA_FUNCTION 0x35C
#घोषणा H_DOWNLOAD_CA_FACILITY 0x364
#घोषणा H_CONTROL_CA_FACILITY  0x368

#घोषणा H_CONTROL_CA_FUNCTION_RESET                   1 /* perक्रमm a reset */
#घोषणा H_CONTROL_CA_FUNCTION_SUSPEND_PROCESS         2 /* suspend a process from being executed */
#घोषणा H_CONTROL_CA_FUNCTION_RESUME_PROCESS          3 /* resume a process to be executed */
#घोषणा H_CONTROL_CA_FUNCTION_READ_ERR_STATE          4 /* पढ़ो the error state */
#घोषणा H_CONTROL_CA_FUNCTION_GET_AFU_ERR             5 /* collect the AFU error buffer */
#घोषणा H_CONTROL_CA_FUNCTION_GET_CONFIG              6 /* collect configuration record */
#घोषणा H_CONTROL_CA_FUNCTION_GET_DOWNLOAD_STATE      7 /* query to वापस करोwnload status */
#घोषणा H_CONTROL_CA_FUNCTION_TERMINATE_PROCESS       8 /* terminate the process beक्रमe completion */
#घोषणा H_CONTROL_CA_FUNCTION_COLLECT_VPD             9 /* collect VPD */
#घोषणा H_CONTROL_CA_FUNCTION_GET_FUNCTION_ERR_INT   11 /* पढ़ो the function-wide error data based on an पूर्णांकerrupt */
#घोषणा H_CONTROL_CA_FUNCTION_ACK_FUNCTION_ERR_INT   12 /* acknowledge function-wide error data based on an पूर्णांकerrupt */
#घोषणा H_CONTROL_CA_FUNCTION_GET_ERROR_LOG          13 /* retrieve the Platक्रमm Log ID (PLID) of an error log */

#घोषणा H_CONTROL_CA_FAULTS_RESPOND_PSL         1
#घोषणा H_CONTROL_CA_FAULTS_RESPOND_AFU         2

#घोषणा H_CONTROL_CA_FACILITY_RESET             1 /* perक्रमm a reset */
#घोषणा H_CONTROL_CA_FACILITY_COLLECT_VPD       2 /* collect VPD */

#घोषणा H_DOWNLOAD_CA_FACILITY_DOWNLOAD         1 /* करोwnload adapter image */
#घोषणा H_DOWNLOAD_CA_FACILITY_VALIDATE         2 /* validate adapter image */


#घोषणा _CXL_LOOP_HCALL(call, rc, retbuf, fn, ...)			\
	अणु								\
		अचिन्हित पूर्णांक delay, total_delay = 0;			\
		u64 token = 0;						\
									\
		स_रखो(retbuf, 0, माप(retbuf));			\
		जबतक (1) अणु						\
			rc = call(fn, retbuf, __VA_ARGS__, token);	\
			token = retbuf[0];				\
			अगर (rc != H_BUSY && !H_IS_LONG_BUSY(rc))	\
				अवरोध;					\
									\
			अगर (rc == H_BUSY)				\
				delay = 10;				\
			अन्यथा						\
				delay = get_दीर्घbusy_msecs(rc);		\
									\
			total_delay += delay;				\
			अगर (total_delay > CXL_HCALL_TIMEOUT) अणु		\
				WARN(1, "Warning: Giving up waiting for CXL hcall " \
					"%#x after %u msec\n", fn, total_delay); \
				rc = H_BUSY;				\
				अवरोध;					\
			पूर्ण						\
			msleep(delay);					\
		पूर्ण							\
	पूर्ण
#घोषणा CXL_H_WAIT_UNTIL_DONE(...)  _CXL_LOOP_HCALL(plpar_hcall, __VA_ARGS__)
#घोषणा CXL_H9_WAIT_UNTIL_DONE(...) _CXL_LOOP_HCALL(plpar_hcall9, __VA_ARGS__)

#घोषणा _PRINT_MSG(rc, क्रमmat, ...)					\
	अणु								\
		अगर ((rc != H_SUCCESS) && (rc != H_CONTINUE))		\
			pr_err(क्रमmat, __VA_ARGS__);			\
		अन्यथा							\
			pr_devel(क्रमmat, __VA_ARGS__);			\
	पूर्ण								\


अटल अक्षर *afu_op_names[] = अणु
	"UNKNOWN_OP",		/* 0 undefined */
	"RESET",		/* 1 */
	"SUSPEND_PROCESS",	/* 2 */
	"RESUME_PROCESS",	/* 3 */
	"READ_ERR_STATE",	/* 4 */
	"GET_AFU_ERR",		/* 5 */
	"GET_CONFIG",		/* 6 */
	"GET_DOWNLOAD_STATE",	/* 7 */
	"TERMINATE_PROCESS",	/* 8 */
	"COLLECT_VPD",		/* 9 */
	"UNKNOWN_OP",		/* 10 undefined */
	"GET_FUNCTION_ERR_INT",	/* 11 */
	"ACK_FUNCTION_ERR_INT",	/* 12 */
	"GET_ERROR_LOG",	/* 13 */
पूर्ण;

अटल अक्षर *control_adapter_op_names[] = अणु
	"UNKNOWN_OP",		/* 0 undefined */
	"RESET",		/* 1 */
	"COLLECT_VPD",		/* 2 */
पूर्ण;

अटल अक्षर *करोwnload_op_names[] = अणु
	"UNKNOWN_OP",		/* 0 undefined */
	"DOWNLOAD",		/* 1 */
	"VALIDATE",		/* 2 */
पूर्ण;

अटल अक्षर *op_str(अचिन्हित पूर्णांक op, अक्षर *name_array[], पूर्णांक array_len)
अणु
	अगर (op >= array_len)
		वापस "UNKNOWN_OP";
	वापस name_array[op];
पूर्ण

#घोषणा OP_STR(op, name_array)      op_str(op, name_array, ARRAY_SIZE(name_array))

#घोषणा OP_STR_AFU(op)              OP_STR(op, afu_op_names)
#घोषणा OP_STR_CONTROL_ADAPTER(op)  OP_STR(op, control_adapter_op_names)
#घोषणा OP_STR_DOWNLOAD_ADAPTER(op) OP_STR(op, करोwnload_op_names)


दीर्घ cxl_h_attach_process(u64 unit_address,
			काष्ठा cxl_process_element_hcall *element,
			u64 *process_token, u64 *mmio_addr, u64 *mmio_size)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	CXL_H_WAIT_UNTIL_DONE(rc, retbuf, H_ATTACH_CA_PROCESS, unit_address, virt_to_phys(element));
	_PRINT_MSG(rc, "cxl_h_attach_process(%#.16llx, %#.16lx): %li\n",
		unit_address, virt_to_phys(element), rc);
	trace_cxl_hcall_attach(unit_address, virt_to_phys(element), retbuf[0], retbuf[1], retbuf[2], rc);

	pr_devel("token: 0x%.8lx mmio_addr: 0x%lx mmio_size: 0x%lx\nProcess Element Structure:\n",
		retbuf[0], retbuf[1], retbuf[2]);
	cxl_dump_debug_buffer(element, माप(*element));

	चयन (rc) अणु
	हाल H_SUCCESS:       /* The process info is attached to the coherent platक्रमm function */
		*process_token = retbuf[0];
		अगर (mmio_addr)
			*mmio_addr = retbuf[1];
		अगर (mmio_size)
			*mmio_size = retbuf[2];
		वापस 0;
	हाल H_PARAMETER:     /* An incorrect parameter was supplied. */
	हाल H_FUNCTION:      /* The function is not supported. */
		वापस -EINVAL;
	हाल H_AUTHORITY:     /* The partition करोes not have authority to perक्रमm this hcall */
	हाल H_RESOURCE:      /* The coherent platक्रमm function करोes not have enough additional resource to attach the process */
	हाल H_HARDWARE:      /* A hardware event prevented the attach operation */
	हाल H_STATE:         /* The coherent platक्रमm function is not in a valid state */
	हाल H_BUSY:
		वापस -EBUSY;
	शेष:
		WARN(1, "Unexpected return code: %lx", rc);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * cxl_h_detach_process - Detach a process element from a coherent
 *                        platक्रमm function.
 */
दीर्घ cxl_h_detach_process(u64 unit_address, u64 process_token)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	CXL_H_WAIT_UNTIL_DONE(rc, retbuf, H_DETACH_CA_PROCESS, unit_address, process_token);
	_PRINT_MSG(rc, "cxl_h_detach_process(%#.16llx, 0x%.8llx): %li\n", unit_address, process_token, rc);
	trace_cxl_hcall_detach(unit_address, process_token, rc);

	चयन (rc) अणु
	हाल H_SUCCESS:       /* The process was detached from the coherent platक्रमm function */
		वापस 0;
	हाल H_PARAMETER:     /* An incorrect parameter was supplied. */
		वापस -EINVAL;
	हाल H_AUTHORITY:     /* The partition करोes not have authority to perक्रमm this hcall */
	हाल H_RESOURCE:      /* The function has page table mappings क्रम MMIO */
	हाल H_HARDWARE:      /* A hardware event prevented the detach operation */
	हाल H_STATE:         /* The coherent platक्रमm function is not in a valid state */
	हाल H_BUSY:
		वापस -EBUSY;
	शेष:
		WARN(1, "Unexpected return code: %lx", rc);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * cxl_h_control_function - This H_CONTROL_CA_FUNCTION hypervisor call allows
 *                          the partition to manipulate or query
 *                          certain coherent platक्रमm function behaviors.
 */
अटल दीर्घ cxl_h_control_function(u64 unit_address, u64 op,
				   u64 p1, u64 p2, u64 p3, u64 p4, u64 *out)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];
	दीर्घ rc;

	CXL_H9_WAIT_UNTIL_DONE(rc, retbuf, H_CONTROL_CA_FUNCTION, unit_address, op, p1, p2, p3, p4);
	_PRINT_MSG(rc, "cxl_h_control_function(%#.16llx, %s(%#llx, %#llx, %#llx, %#llx, R4: %#lx)): %li\n",
		unit_address, OP_STR_AFU(op), p1, p2, p3, p4, retbuf[0], rc);
	trace_cxl_hcall_control_function(unit_address, OP_STR_AFU(op), p1, p2, p3, p4, retbuf[0], rc);

	चयन (rc) अणु
	हाल H_SUCCESS:       /* The operation is completed क्रम the coherent platक्रमm function */
		अगर ((op == H_CONTROL_CA_FUNCTION_GET_FUNCTION_ERR_INT ||
		     op == H_CONTROL_CA_FUNCTION_READ_ERR_STATE ||
		     op == H_CONTROL_CA_FUNCTION_COLLECT_VPD))
			*out = retbuf[0];
		वापस 0;
	हाल H_PARAMETER:     /* An incorrect parameter was supplied. */
	हाल H_FUNCTION:      /* The function is not supported. */
	हाल H_NOT_FOUND:     /* The operation supplied was not valid */
	हाल H_NOT_AVAILABLE: /* The operation cannot be perक्रमmed because the AFU has not been करोwnloaded */
	हाल H_SG_LIST:       /* An block list entry was invalid */
		वापस -EINVAL;
	हाल H_AUTHORITY:     /* The partition करोes not have authority to perक्रमm this hcall */
	हाल H_RESOURCE:      /* The function has page table mappings क्रम MMIO */
	हाल H_HARDWARE:      /* A hardware event prevented the attach operation */
	हाल H_STATE:         /* The coherent platक्रमm function is not in a valid state */
	हाल H_BUSY:
		वापस -EBUSY;
	शेष:
		WARN(1, "Unexpected return code: %lx", rc);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * cxl_h_reset_afu - Perक्रमm a reset to the coherent platक्रमm function.
 */
दीर्घ cxl_h_reset_afu(u64 unit_address)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_RESET,
				0, 0, 0, 0,
				शून्य);
पूर्ण

/*
 * cxl_h_suspend_process - Suspend a process from being executed
 * Parameter1 = process-token as वापसed from H_ATTACH_CA_PROCESS when
 *              process was attached.
 */
दीर्घ cxl_h_suspend_process(u64 unit_address, u64 process_token)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_SUSPEND_PROCESS,
				process_token, 0, 0, 0,
				शून्य);
पूर्ण

/*
 * cxl_h_resume_process - Resume a process to be executed
 * Parameter1 = process-token as वापसed from H_ATTACH_CA_PROCESS when
 *              process was attached.
 */
दीर्घ cxl_h_resume_process(u64 unit_address, u64 process_token)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_RESUME_PROCESS,
				process_token, 0, 0, 0,
				शून्य);
पूर्ण

/*
 * cxl_h_पढ़ो_error_state - Checks the error state of the coherent
 *                          platक्रमm function.
 * R4 contains the error state
 */
दीर्घ cxl_h_पढ़ो_error_state(u64 unit_address, u64 *state)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_READ_ERR_STATE,
				0, 0, 0, 0,
				state);
पूर्ण

/*
 * cxl_h_get_afu_err - collect the AFU error buffer
 * Parameter1 = byte offset पूर्णांकo error buffer to retrieve, valid values
 *              are between 0 and (ibm,error-buffer-size - 1)
 * Parameter2 = 4K aligned real address of error buffer, to be filled in
 * Parameter3 = length of error buffer, valid values are 4K or less
 */
दीर्घ cxl_h_get_afu_err(u64 unit_address, u64 offset,
		u64 buf_address, u64 len)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_GET_AFU_ERR,
				offset, buf_address, len, 0,
				शून्य);
पूर्ण

/*
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
		u64 buf_address, u64 len)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_GET_CONFIG,
				cr_num, offset, buf_address, len,
				शून्य);
पूर्ण

/*
 * cxl_h_terminate_process - Terminate the process beक्रमe completion
 * Parameter1 = process-token as वापसed from H_ATTACH_CA_PROCESS when
 *              process was attached.
 */
दीर्घ cxl_h_terminate_process(u64 unit_address, u64 process_token)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_TERMINATE_PROCESS,
				process_token, 0, 0, 0,
				शून्य);
पूर्ण

/*
 * cxl_h_collect_vpd - Collect VPD क्रम the coherent platक्रमm function.
 * Parameter1 = # of VPD record to retrieve, valid values are between 0
 *              and (ibm,#config-records - 1).
 * Parameter2 = 4K naturally aligned real buffer containing block
 *              list entries
 * Parameter3 = number of block list entries in the block list, valid
 *              values are between 0 and 256
 */
दीर्घ cxl_h_collect_vpd(u64 unit_address, u64 record, u64 list_address,
		       u64 num, u64 *out)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_COLLECT_VPD,
				record, list_address, num, 0,
				out);
पूर्ण

/*
 * cxl_h_get_fn_error_पूर्णांकerrupt - Read the function-wide error data based on an पूर्णांकerrupt
 */
दीर्घ cxl_h_get_fn_error_पूर्णांकerrupt(u64 unit_address, u64 *reg)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_GET_FUNCTION_ERR_INT,
				0, 0, 0, 0, reg);
पूर्ण

/*
 * cxl_h_ack_fn_error_पूर्णांकerrupt - Acknowledge function-wide error data
 *                                based on an पूर्णांकerrupt
 * Parameter1 = value to ग_लिखो to the function-wide error पूर्णांकerrupt रेजिस्टर
 */
दीर्घ cxl_h_ack_fn_error_पूर्णांकerrupt(u64 unit_address, u64 value)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_ACK_FUNCTION_ERR_INT,
				value, 0, 0, 0,
				शून्य);
पूर्ण

/*
 * cxl_h_get_error_log - Retrieve the Platक्रमm Log ID (PLID) of
 *                       an error log
 */
दीर्घ cxl_h_get_error_log(u64 unit_address, u64 value)
अणु
	वापस cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_GET_ERROR_LOG,
				0, 0, 0, 0,
				शून्य);
पूर्ण

/*
 * cxl_h_collect_पूर्णांक_info - Collect पूर्णांकerrupt info about a coherent
 *                          platक्रमm function after an पूर्णांकerrupt occurred.
 */
दीर्घ cxl_h_collect_पूर्णांक_info(u64 unit_address, u64 process_token,
			    काष्ठा cxl_irq_info *info)
अणु
	दीर्घ rc;

	BUG_ON(माप(*info) != माप(अचिन्हित दीर्घ[PLPAR_HCALL9_बफ_मानE]));

	rc = plpar_hcall9(H_COLLECT_CA_INT_INFO, (अचिन्हित दीर्घ *) info,
			unit_address, process_token);
	_PRINT_MSG(rc, "cxl_h_collect_int_info(%#.16llx, 0x%llx): %li\n",
		unit_address, process_token, rc);
	trace_cxl_hcall_collect_पूर्णांक_info(unit_address, process_token, rc);

	चयन (rc) अणु
	हाल H_SUCCESS:     /* The पूर्णांकerrupt info is वापसed in वापस रेजिस्टरs. */
		pr_devel("dsisr:%#llx, dar:%#llx, dsr:%#llx, pid_tid:%#llx, afu_err:%#llx, errstat:%#llx\n",
			info->dsisr, info->dar, info->dsr, info->reserved,
			info->afu_err, info->errstat);
		वापस 0;
	हाल H_PARAMETER:   /* An incorrect parameter was supplied. */
		वापस -EINVAL;
	हाल H_AUTHORITY:   /* The partition करोes not have authority to perक्रमm this hcall. */
	हाल H_HARDWARE:    /* A hardware event prevented the collection of the पूर्णांकerrupt info.*/
	हाल H_STATE:       /* The coherent platक्रमm function is not in a valid state to collect पूर्णांकerrupt info. */
		वापस -EBUSY;
	शेष:
		WARN(1, "Unexpected return code: %lx", rc);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
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
			  u64 control_mask, u64 reset_mask)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	स_रखो(retbuf, 0, माप(retbuf));

	rc = plpar_hcall(H_CONTROL_CA_FAULTS, retbuf, unit_address,
			H_CONTROL_CA_FAULTS_RESPOND_PSL, process_token,
			control_mask, reset_mask);
	_PRINT_MSG(rc, "cxl_h_control_faults(%#.16llx, 0x%llx, %#llx, %#llx): %li (%#lx)\n",
		unit_address, process_token, control_mask, reset_mask,
		rc, retbuf[0]);
	trace_cxl_hcall_control_faults(unit_address, process_token,
				control_mask, reset_mask, retbuf[0], rc);

	चयन (rc) अणु
	हाल H_SUCCESS:    /* Faults were successfully controlled क्रम the function. */
		वापस 0;
	हाल H_PARAMETER:  /* An incorrect parameter was supplied. */
		वापस -EINVAL;
	हाल H_HARDWARE:   /* A hardware event prevented the control of faults. */
	हाल H_STATE:      /* The function was in an invalid state. */
	हाल H_AUTHORITY:  /* The partition करोes not have authority to perक्रमm this hcall; the coherent platक्रमm facilities may need to be licensed. */
		वापस -EBUSY;
	हाल H_FUNCTION:   /* The function is not supported */
	हाल H_NOT_FOUND:  /* The operation supplied was not valid */
		वापस -EINVAL;
	शेष:
		WARN(1, "Unexpected return code: %lx", rc);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * cxl_h_control_facility - This H_CONTROL_CA_FACILITY hypervisor call
 *                          allows the partition to manipulate or query
 *                          certain coherent platक्रमm facility behaviors.
 */
अटल दीर्घ cxl_h_control_facility(u64 unit_address, u64 op,
				   u64 p1, u64 p2, u64 p3, u64 p4, u64 *out)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];
	दीर्घ rc;

	CXL_H9_WAIT_UNTIL_DONE(rc, retbuf, H_CONTROL_CA_FACILITY, unit_address, op, p1, p2, p3, p4);
	_PRINT_MSG(rc, "cxl_h_control_facility(%#.16llx, %s(%#llx, %#llx, %#llx, %#llx, R4: %#lx)): %li\n",
		unit_address, OP_STR_CONTROL_ADAPTER(op), p1, p2, p3, p4, retbuf[0], rc);
	trace_cxl_hcall_control_facility(unit_address, OP_STR_CONTROL_ADAPTER(op), p1, p2, p3, p4, retbuf[0], rc);

	चयन (rc) अणु
	हाल H_SUCCESS:       /* The operation is completed क्रम the coherent platक्रमm facility */
		अगर (op == H_CONTROL_CA_FACILITY_COLLECT_VPD)
			*out = retbuf[0];
		वापस 0;
	हाल H_PARAMETER:     /* An incorrect parameter was supplied. */
	हाल H_FUNCTION:      /* The function is not supported. */
	हाल H_NOT_FOUND:     /* The operation supplied was not valid */
	हाल H_NOT_AVAILABLE: /* The operation cannot be perक्रमmed because the AFU has not been करोwnloaded */
	हाल H_SG_LIST:       /* An block list entry was invalid */
		वापस -EINVAL;
	हाल H_AUTHORITY:     /* The partition करोes not have authority to perक्रमm this hcall */
	हाल H_RESOURCE:      /* The function has page table mappings क्रम MMIO */
	हाल H_HARDWARE:      /* A hardware event prevented the attach operation */
	हाल H_STATE:         /* The coherent platक्रमm facility is not in a valid state */
	हाल H_BUSY:
		वापस -EBUSY;
	शेष:
		WARN(1, "Unexpected return code: %lx", rc);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * cxl_h_reset_adapter - Perक्रमm a reset to the coherent platक्रमm facility.
 */
दीर्घ cxl_h_reset_adapter(u64 unit_address)
अणु
	वापस cxl_h_control_facility(unit_address,
				H_CONTROL_CA_FACILITY_RESET,
				0, 0, 0, 0,
				शून्य);
पूर्ण

/*
 * cxl_h_collect_vpd - Collect VPD क्रम the coherent platक्रमm function.
 * Parameter1 = 4K naturally aligned real buffer containing block
 *              list entries
 * Parameter2 = number of block list entries in the block list, valid
 *              values are between 0 and 256
 */
दीर्घ cxl_h_collect_vpd_adapter(u64 unit_address, u64 list_address,
			       u64 num, u64 *out)
अणु
	वापस cxl_h_control_facility(unit_address,
				H_CONTROL_CA_FACILITY_COLLECT_VPD,
				list_address, num, 0, 0,
				out);
पूर्ण

/*
 * cxl_h_करोwnload_facility - This H_DOWNLOAD_CA_FACILITY
 *                    hypervisor call provide platक्रमm support क्रम
 *                    करोwnloading a base adapter image to the coherent
 *                    platक्रमm facility, and क्रम validating the entire
 *                    image after the करोwnload.
 * Parameters
 *    op: operation to perक्रमm to the coherent platक्रमm function
 *      Download: operation = 1, the base image in the coherent platक्रमm
 *                               facility is first erased, and then
 *                               programmed using the image supplied
 *                               in the scatter/gather list.
 *      Validate: operation = 2, the base image in the coherent platक्रमm
 *                               facility is compared with the image
 *                               supplied in the scatter/gather list.
 *    list_address: 4K naturally aligned real buffer containing
 *                  scatter/gather list entries.
 *    num: number of block list entries in the scatter/gather list.
 */
अटल दीर्घ cxl_h_करोwnload_facility(u64 unit_address, u64 op,
				    u64 list_address, u64 num,
				    u64 *out)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	अचिन्हित पूर्णांक delay, total_delay = 0;
	u64 token = 0;
	दीर्घ rc;

	अगर (*out != 0)
		token = *out;

	स_रखो(retbuf, 0, माप(retbuf));
	जबतक (1) अणु
		rc = plpar_hcall(H_DOWNLOAD_CA_FACILITY, retbuf,
				 unit_address, op, list_address, num,
				 token);
		token = retbuf[0];
		अगर (rc != H_BUSY && !H_IS_LONG_BUSY(rc))
			अवरोध;

		अगर (rc != H_BUSY) अणु
			delay = get_दीर्घbusy_msecs(rc);
			total_delay += delay;
			अगर (total_delay > CXL_HCALL_TIMEOUT_DOWNLOAD) अणु
				WARN(1, "Warning: Giving up waiting for CXL hcall "
					"%#x after %u msec\n",
					H_DOWNLOAD_CA_FACILITY, total_delay);
				rc = H_BUSY;
				अवरोध;
			पूर्ण
			msleep(delay);
		पूर्ण
	पूर्ण
	_PRINT_MSG(rc, "cxl_h_download_facility(%#.16llx, %s(%#llx, %#llx), %#lx): %li\n",
		 unit_address, OP_STR_DOWNLOAD_ADAPTER(op), list_address, num, retbuf[0], rc);
	trace_cxl_hcall_करोwnload_facility(unit_address, OP_STR_DOWNLOAD_ADAPTER(op), list_address, num, retbuf[0], rc);

	चयन (rc) अणु
	हाल H_SUCCESS:       /* The operation is completed क्रम the coherent platक्रमm facility */
		वापस 0;
	हाल H_PARAMETER:     /* An incorrect parameter was supplied */
	हाल H_FUNCTION:      /* The function is not supported. */
	हाल H_SG_LIST:       /* An block list entry was invalid */
	हाल H_BAD_DATA:      /* Image verअगरication failed */
		वापस -EINVAL;
	हाल H_AUTHORITY:     /* The partition करोes not have authority to perक्रमm this hcall */
	हाल H_RESOURCE:      /* The function has page table mappings क्रम MMIO */
	हाल H_HARDWARE:      /* A hardware event prevented the attach operation */
	हाल H_STATE:         /* The coherent platक्रमm facility is not in a valid state */
	हाल H_BUSY:
		वापस -EBUSY;
	हाल H_CONTINUE:
		*out = retbuf[0];
		वापस 1;  /* More data is needed क्रम the complete image */
	शेष:
		WARN(1, "Unexpected return code: %lx", rc);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * cxl_h_करोwnload_adapter_image - Download the base image to the coherent
 *                                platक्रमm facility.
 */
दीर्घ cxl_h_करोwnload_adapter_image(u64 unit_address,
				  u64 list_address, u64 num,
				  u64 *out)
अणु
	वापस cxl_h_करोwnload_facility(unit_address,
				       H_DOWNLOAD_CA_FACILITY_DOWNLOAD,
				       list_address, num, out);
पूर्ण

/*
 * cxl_h_validate_adapter_image - Validate the base image in the coherent
 *                                platक्रमm facility.
 */
दीर्घ cxl_h_validate_adapter_image(u64 unit_address,
				  u64 list_address, u64 num,
				  u64 *out)
अणु
	वापस cxl_h_करोwnload_facility(unit_address,
				       H_DOWNLOAD_CA_FACILITY_VALIDATE,
				       list_address, num, out);
पूर्ण
