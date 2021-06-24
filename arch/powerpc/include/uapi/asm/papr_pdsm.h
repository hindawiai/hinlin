<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * PAPR nvDimm Specअगरic Methods (PDSM) and काष्ठाs क्रम libndctl
 *
 * (C) Copyright IBM 2020
 *
 * Author: Vaibhav Jain <vaibhav at linux.ibm.com>
 */

#अगर_अघोषित _UAPI_ASM_POWERPC_PAPR_PDSM_H_
#घोषणा _UAPI_ASM_POWERPC_PAPR_PDSM_H_

#समावेश <linux/types.h>
#समावेश <linux/ndctl.h>

/*
 * PDSM Envelope:
 *
 * The ioctl ND_CMD_CALL exchange data between user-space and kernel via
 * envelope which consists of 2 headers sections and payload sections as
 * illustrated below:
 *  +-----------------+---------------+---------------------------+
 *  |   64-Bytes      |   8-Bytes     |       Max 184-Bytes       |
 *  +-----------------+---------------+---------------------------+
 *  | ND-HEADER       |  PDSM-HEADER  |      PDSM-PAYLOAD         |
 *  +-----------------+---------------+---------------------------+
 *  | nd_family       |               |                           |
 *  | nd_size_out     | cmd_status    |                           |
 *  | nd_size_in      | reserved      |     nd_pdsm_payload       |
 *  | nd_command      | payload   --> |                           |
 *  | nd_fw_size      |               |                           |
 *  | nd_payload ---> |               |                           |
 *  +---------------+-----------------+---------------------------+
 *
 * ND Header:
 * This is the generic libnvdimm header described as 'struct nd_cmd_pkg'
 * which is पूर्णांकerpreted by libnvdimm beक्रमe passed on to papr_scm. Important
 * member fields used are:
 * 'nd_family'		: (In) NVDIMM_FAMILY_PAPR_SCM
 * 'nd_size_in'		: (In) PDSM-HEADER + PDSM-IN-PAYLOAD (usually 0)
 * 'nd_size_out'        : (In) PDSM-HEADER + PDSM-RETURN-PAYLOAD
 * 'nd_command'         : (In) One of PAPR_PDSM_XXX
 * 'nd_fw_size'         : (Out) PDSM-HEADER + size of actual payload वापसed
 *
 * PDSM Header:
 * This is papr-scm specअगरic header that precedes the payload. This is defined
 * as nd_cmd_pdsm_pkg.  Following fields aare available in this header:
 *
 * 'cmd_status'		: (Out) Errors अगर any encountered जबतक servicing PDSM.
 * 'reserved'		: Not used, reserved क्रम future and should be set to 0.
 * 'payload'            : A जोड़ of all the possible payload काष्ठाs
 *
 * PDSM Payload:
 *
 * The layout of the PDSM Payload is defined by various काष्ठाs shared between
 * papr_scm and libndctl so that contents of payload can be पूर्णांकerpreted. As such
 * its defined as a जोड़ of all possible payload काष्ठाs as
 * 'union nd_pdsm_payload'. Based on the value of 'nd_cmd_pkg.nd_command'
 * appropriate member of the जोड़ is accessed.
 */

/* Max payload size that we can handle */
#घोषणा ND_PDSM_PAYLOAD_MAX_SIZE 184

/* Max payload size that we can handle */
#घोषणा ND_PDSM_HDR_SIZE \
	(माप(काष्ठा nd_pkg_pdsm) - ND_PDSM_PAYLOAD_MAX_SIZE)

/* Various nvdimm health indicators */
#घोषणा PAPR_PDSM_DIMM_HEALTHY       0
#घोषणा PAPR_PDSM_DIMM_UNHEALTHY     1
#घोषणा PAPR_PDSM_DIMM_CRITICAL      2
#घोषणा PAPR_PDSM_DIMM_FATAL         3

/* काष्ठा nd_papr_pdsm_health.extension_flags field flags */

/* Indicate that the 'dimm_fuel_gauge' field is valid */
#घोषणा PDSM_DIMM_HEALTH_RUN_GAUGE_VALID 1

/*
 * Struct exchanged between kernel & ndctl in क्रम PAPR_PDSM_HEALTH
 * Various flags indicate the health status of the dimm.
 *
 * extension_flags	: Any extension fields present in the काष्ठा.
 * dimm_unarmed		: Dimm not armed. So contents wont persist.
 * dimm_bad_shutकरोwn	: Previous shutकरोwn did not persist contents.
 * dimm_bad_restore	: Contents from previous shutकरोwn werent restored.
 * dimm_scrubbed	: Contents of the dimm have been scrubbed.
 * dimm_locked		: Contents of the dimm cant be modअगरied until CEC reboot
 * dimm_encrypted	: Contents of dimm are encrypted.
 * dimm_health		: Dimm health indicator. One of PAPR_PDSM_DIMM_XXXX
 * dimm_fuel_gauge	: Lअगरe reमुख्यing of DIMM as a percentage from 0-100
 */
काष्ठा nd_papr_pdsm_health अणु
	जोड़ अणु
		काष्ठा अणु
			__u32 extension_flags;
			__u8 dimm_unarmed;
			__u8 dimm_bad_shutकरोwn;
			__u8 dimm_bad_restore;
			__u8 dimm_scrubbed;
			__u8 dimm_locked;
			__u8 dimm_encrypted;
			__u16 dimm_health;

			/* Extension flag PDSM_DIMM_HEALTH_RUN_GAUGE_VALID */
			__u16 dimm_fuel_gauge;
		पूर्ण;
		__u8 buf[ND_PDSM_PAYLOAD_MAX_SIZE];
	पूर्ण;
पूर्ण;

/*
 * Methods to be embedded in ND_CMD_CALL request. These are sent to the kernel
 * via 'nd_cmd_pkg.nd_command' member of the ioctl काष्ठा
 */
क्रमागत papr_pdsm अणु
	PAPR_PDSM_MIN = 0x0,
	PAPR_PDSM_HEALTH,
	PAPR_PDSM_MAX,
पूर्ण;

/* Maximal जोड़ that can hold all possible payload types */
जोड़ nd_pdsm_payload अणु
	काष्ठा nd_papr_pdsm_health health;
	__u8 buf[ND_PDSM_PAYLOAD_MAX_SIZE];
पूर्ण __packed;

/*
 * PDSM-header + payload expected with ND_CMD_CALL ioctl from libnvdimm
 * Valid member of जोड़ 'payload' is identified via 'nd_cmd_pkg.nd_command'
 * that should always precede this काष्ठा when sent to papr_scm via CMD_CALL
 * पूर्णांकerface.
 */
काष्ठा nd_pkg_pdsm अणु
	__s32 cmd_status;	/* Out: Sub-cmd status वापसed back */
	__u16 reserved[2];	/* Ignored and to be set as '0' */
	जोड़ nd_pdsm_payload payload;
पूर्ण __packed;

#पूर्ण_अगर /* _UAPI_ASM_POWERPC_PAPR_PDSM_H_ */
