<शैली गुरु>
/*
 * Copyright (c) 2014-2016, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License क्रम
 * more details.
 */
#अगर_अघोषित __NDCTL_H__
#घोषणा __NDCTL_H__

#समावेश <linux/types.h>

काष्ठा nd_cmd_dimm_flags अणु
	__u32 status;
	__u32 flags;
पूर्ण __packed;

काष्ठा nd_cmd_get_config_size अणु
	__u32 status;
	__u32 config_size;
	__u32 max_xfer;
पूर्ण __packed;

काष्ठा nd_cmd_get_config_data_hdr अणु
	__u32 in_offset;
	__u32 in_length;
	__u32 status;
	__u8 out_buf[0];
पूर्ण __packed;

काष्ठा nd_cmd_set_config_hdr अणु
	__u32 in_offset;
	__u32 in_length;
	__u8 in_buf[0];
पूर्ण __packed;

काष्ठा nd_cmd_venकरोr_hdr अणु
	__u32 opcode;
	__u32 in_length;
	__u8 in_buf[0];
पूर्ण __packed;

काष्ठा nd_cmd_venकरोr_tail अणु
	__u32 status;
	__u32 out_length;
	__u8 out_buf[0];
पूर्ण __packed;

काष्ठा nd_cmd_ars_cap अणु
	__u64 address;
	__u64 length;
	__u32 status;
	__u32 max_ars_out;
	__u32 clear_err_unit;
	__u16 flags;
	__u16 reserved;
पूर्ण __packed;

काष्ठा nd_cmd_ars_start अणु
	__u64 address;
	__u64 length;
	__u16 type;
	__u8 flags;
	__u8 reserved[5];
	__u32 status;
	__u32 scrub_समय;
पूर्ण __packed;

काष्ठा nd_cmd_ars_status अणु
	__u32 status;
	__u32 out_length;
	__u64 address;
	__u64 length;
	__u64 restart_address;
	__u64 restart_length;
	__u16 type;
	__u16 flags;
	__u32 num_records;
	काष्ठा nd_ars_record अणु
		__u32 handle;
		__u32 reserved;
		__u64 err_address;
		__u64 length;
	पूर्ण __packed records[0];
पूर्ण __packed;

काष्ठा nd_cmd_clear_error अणु
	__u64 address;
	__u64 length;
	__u32 status;
	__u8 reserved[4];
	__u64 cleared;
पूर्ण __packed;

क्रमागत अणु
	ND_CMD_IMPLEMENTED = 0,

	/* bus commands */
	ND_CMD_ARS_CAP = 1,
	ND_CMD_ARS_START = 2,
	ND_CMD_ARS_STATUS = 3,
	ND_CMD_CLEAR_ERROR = 4,

	/* per-dimm commands */
	ND_CMD_SMART = 1,
	ND_CMD_SMART_THRESHOLD = 2,
	ND_CMD_DIMM_FLAGS = 3,
	ND_CMD_GET_CONFIG_SIZE = 4,
	ND_CMD_GET_CONFIG_DATA = 5,
	ND_CMD_SET_CONFIG_DATA = 6,
	ND_CMD_VENDOR_EFFECT_LOG_SIZE = 7,
	ND_CMD_VENDOR_EFFECT_LOG = 8,
	ND_CMD_VENDOR = 9,
	ND_CMD_CALL = 10,
पूर्ण;

क्रमागत अणु
	ND_ARS_VOLATILE = 1,
	ND_ARS_PERSISTENT = 2,
	ND_ARS_RETURN_PREV_DATA = 1 << 1,
	ND_CONFIG_LOCKED = 1,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *nvdimm_bus_cmd_name(अचिन्हित cmd)
अणु
	चयन (cmd) अणु
	हाल ND_CMD_ARS_CAP:		वापस "ars_cap";
	हाल ND_CMD_ARS_START:		वापस "ars_start";
	हाल ND_CMD_ARS_STATUS:		वापस "ars_status";
	हाल ND_CMD_CLEAR_ERROR:	वापस "clear_error";
	हाल ND_CMD_CALL:		वापस "cmd_call";
	शेष:			वापस "unknown";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *nvdimm_cmd_name(अचिन्हित cmd)
अणु
	चयन (cmd) अणु
	हाल ND_CMD_SMART:			वापस "smart";
	हाल ND_CMD_SMART_THRESHOLD:		वापस "smart_thresh";
	हाल ND_CMD_DIMM_FLAGS:			वापस "flags";
	हाल ND_CMD_GET_CONFIG_SIZE:		वापस "get_size";
	हाल ND_CMD_GET_CONFIG_DATA:		वापस "get_data";
	हाल ND_CMD_SET_CONFIG_DATA:		वापस "set_data";
	हाल ND_CMD_VENDOR_EFFECT_LOG_SIZE:	वापस "effect_size";
	हाल ND_CMD_VENDOR_EFFECT_LOG:		वापस "effect_log";
	हाल ND_CMD_VENDOR:			वापस "vendor";
	हाल ND_CMD_CALL:			वापस "cmd_call";
	शेष:				वापस "unknown";
	पूर्ण
पूर्ण

#घोषणा ND_IOCTL 'N'

#घोषणा ND_IOCTL_DIMM_FLAGS		_IOWR(ND_IOCTL, ND_CMD_DIMM_FLAGS,\
					काष्ठा nd_cmd_dimm_flags)

#घोषणा ND_IOCTL_GET_CONFIG_SIZE	_IOWR(ND_IOCTL, ND_CMD_GET_CONFIG_SIZE,\
					काष्ठा nd_cmd_get_config_size)

#घोषणा ND_IOCTL_GET_CONFIG_DATA	_IOWR(ND_IOCTL, ND_CMD_GET_CONFIG_DATA,\
					काष्ठा nd_cmd_get_config_data_hdr)

#घोषणा ND_IOCTL_SET_CONFIG_DATA	_IOWR(ND_IOCTL, ND_CMD_SET_CONFIG_DATA,\
					काष्ठा nd_cmd_set_config_hdr)

#घोषणा ND_IOCTL_VENDOR			_IOWR(ND_IOCTL, ND_CMD_VENDOR,\
					काष्ठा nd_cmd_venकरोr_hdr)

#घोषणा ND_IOCTL_ARS_CAP		_IOWR(ND_IOCTL, ND_CMD_ARS_CAP,\
					काष्ठा nd_cmd_ars_cap)

#घोषणा ND_IOCTL_ARS_START		_IOWR(ND_IOCTL, ND_CMD_ARS_START,\
					काष्ठा nd_cmd_ars_start)

#घोषणा ND_IOCTL_ARS_STATUS		_IOWR(ND_IOCTL, ND_CMD_ARS_STATUS,\
					काष्ठा nd_cmd_ars_status)

#घोषणा ND_IOCTL_CLEAR_ERROR		_IOWR(ND_IOCTL, ND_CMD_CLEAR_ERROR,\
					काष्ठा nd_cmd_clear_error)

#घोषणा ND_DEVICE_DIMM 1            /* nd_dimm: container क्रम "config data" */
#घोषणा ND_DEVICE_REGION_PMEM 2     /* nd_region: (parent of PMEM namespaces) */
#घोषणा ND_DEVICE_REGION_BLK 3      /* nd_region: (parent of BLK namespaces) */
#घोषणा ND_DEVICE_NAMESPACE_IO 4    /* legacy persistent memory */
#घोषणा ND_DEVICE_NAMESPACE_PMEM 5  /* PMEM namespace (may alias with BLK) */
#घोषणा ND_DEVICE_NAMESPACE_BLK 6   /* BLK namespace (may alias with PMEM) */
#घोषणा ND_DEVICE_DAX_PMEM 7        /* Device DAX पूर्णांकerface to pmem */

क्रमागत nd_driver_flags अणु
	ND_DRIVER_DIMM            = 1 << ND_DEVICE_DIMM,
	ND_DRIVER_REGION_PMEM     = 1 << ND_DEVICE_REGION_PMEM,
	ND_DRIVER_REGION_BLK      = 1 << ND_DEVICE_REGION_BLK,
	ND_DRIVER_NAMESPACE_IO    = 1 << ND_DEVICE_NAMESPACE_IO,
	ND_DRIVER_NAMESPACE_PMEM  = 1 << ND_DEVICE_NAMESPACE_PMEM,
	ND_DRIVER_NAMESPACE_BLK   = 1 << ND_DEVICE_NAMESPACE_BLK,
	ND_DRIVER_DAX_PMEM	  = 1 << ND_DEVICE_DAX_PMEM,
पूर्ण;

क्रमागत ars_masks अणु
	ARS_STATUS_MASK = 0x0000FFFF,
	ARS_EXT_STATUS_SHIFT = 16,
पूर्ण;

/*
 * काष्ठा nd_cmd_pkg
 *
 * is a wrapper to a quasi pass thru पूर्णांकerface क्रम invoking firmware
 * associated with nvdimms.
 *
 * INPUT PARAMETERS
 *
 * nd_family corresponds to the firmware (e.g. DSM) पूर्णांकerface.
 *
 * nd_command are the function index advertised by the firmware.
 *
 * nd_size_in is the size of the input parameters being passed to firmware
 *
 * OUTPUT PARAMETERS
 *
 * nd_fw_size is the size of the data firmware wants to वापस क्रम
 * the call.  If nd_fw_size is greater than size of nd_size_out, only
 * the first nd_size_out bytes are वापसed.
 */

काष्ठा nd_cmd_pkg अणु
	__u64   nd_family;		/* family of commands */
	__u64   nd_command;
	__u32   nd_size_in;		/* INPUT: size of input args */
	__u32   nd_size_out;		/* INPUT: size of payload */
	__u32   nd_reserved2[9];	/* reserved must be zero */
	__u32   nd_fw_size;		/* OUTPUT: size fw wants to वापस */
	अचिन्हित अक्षर nd_payload[];	/* Contents of call      */
पूर्ण;

/* These NVDIMM families represent pre-standardization command sets */
#घोषणा NVDIMM_FAMILY_INTEL 0
#घोषणा NVDIMM_FAMILY_HPE1 1
#घोषणा NVDIMM_FAMILY_HPE2 2
#घोषणा NVDIMM_FAMILY_MSFT 3
#घोषणा NVDIMM_FAMILY_HYPERV 4
#घोषणा NVDIMM_FAMILY_PAPR 5
#घोषणा NVDIMM_FAMILY_MAX NVDIMM_FAMILY_PAPR

#घोषणा NVDIMM_BUS_FAMILY_NFIT 0
#घोषणा NVDIMM_BUS_FAMILY_INTEL 1
#घोषणा NVDIMM_BUS_FAMILY_MAX NVDIMM_BUS_FAMILY_INTEL

#घोषणा ND_IOCTL_CALL			_IOWR(ND_IOCTL, ND_CMD_CALL,\
					काष्ठा nd_cmd_pkg)

#पूर्ण_अगर /* __NDCTL_H__ */
