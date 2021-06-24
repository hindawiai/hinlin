<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2017-2018, Intel Corporation
 */

#अगर_अघोषित __STRATIX10_SMC_H
#घोषणा __STRATIX10_SMC_H

#समावेश <linux/arm-smccc.h>
#समावेश <linux/bitops.h>

/**
 * This file defines the Secure Monitor Call (SMC) message protocol used क्रम
 * service layer driver in normal world (EL1) to communicate with secure
 * monitor software in Secure Monitor Exception Level 3 (EL3).
 *
 * This file is shared with secure firmware (FW) which is out of kernel tree.
 *
 * An ARM SMC inकाष्ठाion takes a function identअगरier and up to 6 64-bit
 * रेजिस्टर values as arguments, and can वापस up to 4 64-bit रेजिस्टर
 * value. The operation of the secure monitor is determined by the parameter
 * values passed in through रेजिस्टरs.
 *
 * EL1 and EL3 communicates poपूर्णांकer as physical address rather than the
 * भव address.
 *
 * Functions specअगरied by ARM SMC Calling convention:
 *
 * FAST call executes atomic operations, वापसs when the requested operation
 * has completed.
 * STD call starts a operation which can be preempted by a non-secure
 * पूर्णांकerrupt. The call can वापस beक्रमe the requested operation has
 * completed.
 *
 * a0..a7 is used as रेजिस्टर names in the descriptions below, on arm32
 * that translates to r0..r7 and on arm64 to w0..w7.
 */

/**
 * @func_num: function ID
 */
#घोषणा INTEL_SIP_SMC_STD_CALL_VAL(func_num) \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_STD_CALL, ARM_SMCCC_SMC_64, \
	ARM_SMCCC_OWNER_SIP, (func_num))

#घोषणा INTEL_SIP_SMC_FAST_CALL_VAL(func_num) \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL, ARM_SMCCC_SMC_64, \
	ARM_SMCCC_OWNER_SIP, (func_num))

/**
 * Return values in INTEL_SIP_SMC_* call
 *
 * INTEL_SIP_SMC_RETURN_UNKNOWN_FUNCTION:
 * Secure monitor software करोesn't recognize the request.
 *
 * INTEL_SIP_SMC_STATUS_OK:
 * Secure monitor software accepts the service client's request.
 *
 * INTEL_SIP_SMC_STATUS_BUSY:
 * Secure monitor software is still processing service client's request.
 *
 * INTEL_SIP_SMC_STATUS_REJECTED:
 * Secure monitor software reject the service client's request.
 *
 * INTEL_SIP_SMC_STATUS_ERROR:
 * There is error during the process of service request.
 *
 * INTEL_SIP_SMC_RSU_ERROR:
 * There is error during the process of remote status update request.
 */
#घोषणा INTEL_SIP_SMC_RETURN_UNKNOWN_FUNCTION		0xFFFFFFFF
#घोषणा INTEL_SIP_SMC_STATUS_OK				0x0
#घोषणा INTEL_SIP_SMC_STATUS_BUSY			0x1
#घोषणा INTEL_SIP_SMC_STATUS_REJECTED			0x2
#घोषणा INTEL_SIP_SMC_STATUS_ERROR			0x4
#घोषणा INTEL_SIP_SMC_RSU_ERROR				0x7

/**
 * Request INTEL_SIP_SMC_FPGA_CONFIG_START
 *
 * Sync call used by service driver at EL1 to request the FPGA in EL3 to
 * be prepare to receive a new configuration.
 *
 * Call रेजिस्टर usage:
 * a0: INTEL_SIP_SMC_FPGA_CONFIG_START.
 * a1: flag क्रम full or partial configuration. 0 क्रम full and 1 क्रम partial
 * configuration.
 * a2-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK, or INTEL_SIP_SMC_STATUS_ERROR.
 * a1-3: not used.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_START 1
#घोषणा INTEL_SIP_SMC_FPGA_CONFIG_START \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_START)

/**
 * Request INTEL_SIP_SMC_FPGA_CONFIG_WRITE
 *
 * Async call used by service driver at EL1 to provide FPGA configuration data
 * to secure world.
 *
 * Call रेजिस्टर usage:
 * a0: INTEL_SIP_SMC_FPGA_CONFIG_WRITE.
 * a1: 64bit physical address of the configuration data memory block
 * a2: Size of configuration data block.
 * a3-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK, INTEL_SIP_SMC_STATUS_BUSY or
 * INTEL_SIP_SMC_STATUS_ERROR.
 * a1: 64bit physical address of 1st completed memory block अगर any completed
 * block, otherwise zero value.
 * a2: 64bit physical address of 2nd completed memory block अगर any completed
 * block, otherwise zero value.
 * a3: 64bit physical address of 3rd completed memory block अगर any completed
 * block, otherwise zero value.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_WRITE 2
#घोषणा INTEL_SIP_SMC_FPGA_CONFIG_WRITE \
	INTEL_SIP_SMC_STD_CALL_VAL(INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_WRITE)

/**
 * Request INTEL_SIP_SMC_FPGA_CONFIG_COMPLETED_WRITE
 *
 * Sync call used by service driver at EL1 to track the completed ग_लिखो
 * transactions. This request is called after INTEL_SIP_SMC_FPGA_CONFIG_WRITE
 * call वापसs INTEL_SIP_SMC_STATUS_BUSY.
 *
 * Call रेजिस्टर usage:
 * a0: INTEL_SIP_SMC_FPGA_CONFIG_COMPLETED_WRITE.
 * a1-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK, INTEL_SIP_SMC_FPGA_BUSY or
 * INTEL_SIP_SMC_STATUS_ERROR.
 * a1: 64bit physical address of 1st completed memory block.
 * a2: 64bit physical address of 2nd completed memory block अगर
 * any completed block, otherwise zero value.
 * a3: 64bit physical address of 3rd completed memory block अगर
 * any completed block, otherwise zero value.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_COMPLETED_WRITE 3
#घोषणा INTEL_SIP_SMC_FPGA_CONFIG_COMPLETED_WRITE \
INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_COMPLETED_WRITE)

/**
 * Request INTEL_SIP_SMC_FPGA_CONFIG_ISDONE
 *
 * Sync call used by service driver at EL1 to inक्रमm secure world that all
 * data are sent, to check whether or not the secure world had completed
 * the FPGA configuration process.
 *
 * Call रेजिस्टर usage:
 * a0: INTEL_SIP_SMC_FPGA_CONFIG_ISDONE.
 * a1-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK, INTEL_SIP_SMC_STATUS_BUSY or
 * INTEL_SIP_SMC_STATUS_ERROR.
 * a1-3: not used.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_ISDONE 4
#घोषणा INTEL_SIP_SMC_FPGA_CONFIG_ISDONE \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_ISDONE)

/**
 * Request INTEL_SIP_SMC_FPGA_CONFIG_GET_MEM
 *
 * Sync call used by service driver at EL1 to query the physical address of
 * memory block reserved by secure monitor software.
 *
 * Call रेजिस्टर usage:
 * a0:INTEL_SIP_SMC_FPGA_CONFIG_GET_MEM.
 * a1-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK or INTEL_SIP_SMC_STATUS_ERROR.
 * a1: start of physical address of reserved memory block.
 * a2: size of reserved memory block.
 * a3: not used.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_GET_MEM 5
#घोषणा INTEL_SIP_SMC_FPGA_CONFIG_GET_MEM \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_GET_MEM)

/**
 * Request INTEL_SIP_SMC_FPGA_CONFIG_LOOPBACK
 *
 * For SMC loop-back mode only, used क्रम पूर्णांकernal पूर्णांकegration, debugging
 * or troubleshooting.
 *
 * Call रेजिस्टर usage:
 * a0: INTEL_SIP_SMC_FPGA_CONFIG_LOOPBACK.
 * a1-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK or INTEL_SIP_SMC_STATUS_ERROR.
 * a1-3: not used.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_LOOPBACK 6
#घोषणा INTEL_SIP_SMC_FPGA_CONFIG_LOOPBACK \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_FPGA_CONFIG_LOOPBACK)

/**
 * Request INTEL_SIP_SMC_REG_READ
 *
 * Read a रक्षित रेजिस्टर at EL3
 *
 * Call रेजिस्टर usage:
 * a0: INTEL_SIP_SMC_REG_READ.
 * a1: रेजिस्टर address.
 * a2-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK or INTEL_SIP_SMC_REG_ERROR.
 * a1: value in the रेजिस्टर
 * a2-3: not used.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_REG_READ 7
#घोषणा INTEL_SIP_SMC_REG_READ \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_REG_READ)

/**
 * Request INTEL_SIP_SMC_REG_WRITE
 *
 * Write a रक्षित रेजिस्टर at EL3
 *
 * Call रेजिस्टर usage:
 * a0: INTEL_SIP_SMC_REG_WRITE.
 * a1: रेजिस्टर address
 * a2: value to program पूर्णांकo रेजिस्टर.
 * a3-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK or INTEL_SIP_SMC_REG_ERROR.
 * a1-3: not used.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_REG_WRITE 8
#घोषणा INTEL_SIP_SMC_REG_WRITE \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_REG_WRITE)

/**
 * Request INTEL_SIP_SMC_FUNCID_REG_UPDATE
 *
 * Update one or more bits in a रक्षित रेजिस्टर at EL3 using a
 * पढ़ो-modअगरy-ग_लिखो operation.
 *
 * Call रेजिस्टर usage:
 * a0: INTEL_SIP_SMC_REG_UPDATE.
 * a1: रेजिस्टर address
 * a2: ग_लिखो Mask.
 * a3: value to ग_लिखो.
 * a4-7: not used.
 *
 * Return status:
 * a0: INTEL_SIP_SMC_STATUS_OK or INTEL_SIP_SMC_REG_ERROR.
 * a1-3: Not used.
 */
#घोषणा INTEL_SIP_SMC_FUNCID_REG_UPDATE 9
#घोषणा INTEL_SIP_SMC_REG_UPDATE \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_REG_UPDATE)

/**
 * Request INTEL_SIP_SMC_RSU_STATUS
 *
 * Request remote status update boot log, call is synchronous.
 *
 * Call रेजिस्टर usage:
 * a0 INTEL_SIP_SMC_RSU_STATUS
 * a1-7 not used
 *
 * Return status
 * a0: Current Image
 * a1: Last Failing Image
 * a2: Version | State
 * a3: Error details | Error location
 *
 * Or
 *
 * a0: INTEL_SIP_SMC_RSU_ERROR
 */
#घोषणा INTEL_SIP_SMC_FUNCID_RSU_STATUS 11
#घोषणा INTEL_SIP_SMC_RSU_STATUS \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_RSU_STATUS)

/**
 * Request INTEL_SIP_SMC_RSU_UPDATE
 *
 * Request to set the offset of the bitstream to boot after reboot, call
 * is synchronous.
 *
 * Call रेजिस्टर usage:
 * a0 INTEL_SIP_SMC_RSU_UPDATE
 * a1 64bit physical address of the configuration data memory in flash
 * a2-7 not used
 *
 * Return status
 * a0 INTEL_SIP_SMC_STATUS_OK
 */
#घोषणा INTEL_SIP_SMC_FUNCID_RSU_UPDATE 12
#घोषणा INTEL_SIP_SMC_RSU_UPDATE \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_RSU_UPDATE)

/**
 * Request INTEL_SIP_SMC_ECC_DBE
 *
 * Sync call used by service driver at EL1 to alert EL3 that a Double
 * Bit ECC error has occurred.
 *
 * Call रेजिस्टर usage:
 * a0 INTEL_SIP_SMC_ECC_DBE
 * a1 SysManager Double Bit Error value
 * a2-7 not used
 *
 * Return status
 * a0 INTEL_SIP_SMC_STATUS_OK
 */
#घोषणा INTEL_SIP_SMC_FUNCID_ECC_DBE 13
#घोषणा INTEL_SIP_SMC_ECC_DBE \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_ECC_DBE)

#पूर्ण_अगर

/**
 * Request INTEL_SIP_SMC_RSU_NOTIFY
 *
 * Sync call used by service driver at EL1 to report hard processor
 * प्रणाली execution stage to firmware
 *
 * Call रेजिस्टर usage:
 * a0 INTEL_SIP_SMC_RSU_NOTIFY
 * a1 32bit value representing hard processor प्रणाली execution stage
 * a2-7 not used
 *
 * Return status
 * a0 INTEL_SIP_SMC_STATUS_OK
 */
#घोषणा INTEL_SIP_SMC_FUNCID_RSU_NOTIFY 14
#घोषणा INTEL_SIP_SMC_RSU_NOTIFY \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_RSU_NOTIFY)

/**
 * Request INTEL_SIP_SMC_RSU_RETRY_COUNTER
 *
 * Sync call used by service driver at EL1 to query RSU retry counter
 *
 * Call रेजिस्टर usage:
 * a0 INTEL_SIP_SMC_RSU_RETRY_COUNTER
 * a1-7 not used
 *
 * Return status
 * a0 INTEL_SIP_SMC_STATUS_OK
 * a1 the retry counter
 *
 * Or
 *
 * a0 INTEL_SIP_SMC_RSU_ERROR
 */
#घोषणा INTEL_SIP_SMC_FUNCID_RSU_RETRY_COUNTER 15
#घोषणा INTEL_SIP_SMC_RSU_RETRY_COUNTER \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_RSU_RETRY_COUNTER)

/**
 * Request INTEL_SIP_SMC_RSU_DCMF_VERSION
 *
 * Sync call used by service driver at EL1 to query DCMF (Decision
 * Configuration Management Firmware) version from FW
 *
 * Call रेजिस्टर usage:
 * a0 INTEL_SIP_SMC_RSU_DCMF_VERSION
 * a1-7 not used
 *
 * Return status
 * a0 INTEL_SIP_SMC_STATUS_OK
 * a1 dcmf1 | dcmf0
 * a2 dcmf3 | dcmf2
 *
 * Or
 *
 * a0 INTEL_SIP_SMC_RSU_ERROR
 */
#घोषणा INTEL_SIP_SMC_FUNCID_RSU_DCMF_VERSION 16
#घोषणा INTEL_SIP_SMC_RSU_DCMF_VERSION \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_RSU_DCMF_VERSION)

/**
 * Request INTEL_SIP_SMC_RSU_MAX_RETRY
 *
 * Sync call used by service driver at EL1 to query max retry value from FW
 *
 * Call रेजिस्टर usage:
 * a0 INTEL_SIP_SMC_RSU_MAX_RETRY
 * a1-7 not used
 *
 * Return status
 * a0 INTEL_SIP_SMC_STATUS_OK
 * a1 max retry value
 *
 * Or
 * a0 INTEL_SIP_SMC_RSU_ERROR
 */
#घोषणा INTEL_SIP_SMC_FUNCID_RSU_MAX_RETRY 18
#घोषणा INTEL_SIP_SMC_RSU_MAX_RETRY \
	INTEL_SIP_SMC_FAST_CALL_VAL(INTEL_SIP_SMC_FUNCID_RSU_MAX_RETRY)
