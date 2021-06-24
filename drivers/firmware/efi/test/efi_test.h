<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * EFI Test driver Header
 *
 * Copyright(C) 2012-2016 Canonical Ltd.
 *
 */

#अगर_अघोषित _DRIVERS_FIRMWARE_EFI_TEST_H_
#घोषणा _DRIVERS_FIRMWARE_EFI_TEST_H_

#समावेश <linux/efi.h>

काष्ठा efi_getvariable अणु
	efi_अक्षर16_t	*variable_name;
	efi_guid_t	*venकरोr_guid;
	u32		*attributes;
	अचिन्हित दीर्घ	*data_size;
	व्योम		*data;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_setvariable अणु
	efi_अक्षर16_t	*variable_name;
	efi_guid_t	*venकरोr_guid;
	u32		attributes;
	अचिन्हित दीर्घ	data_size;
	व्योम		*data;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_getnextvariablename अणु
	अचिन्हित दीर्घ	*variable_name_size;
	efi_अक्षर16_t	*variable_name;
	efi_guid_t	*venकरोr_guid;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_queryvariableinfo अणु
	u32		attributes;
	u64		*maximum_variable_storage_size;
	u64		*reमुख्यing_variable_storage_size;
	u64		*maximum_variable_size;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_समय_लो अणु
	efi_समय_प्रकार	*समय;
	efi_समय_cap_t	*capabilities;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_समय_रखो अणु
	efi_समय_प्रकार	*समय;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_getwakeupसमय अणु
	efi_bool_t	*enabled;
	efi_bool_t	*pending;
	efi_समय_प्रकार	*समय;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_setwakeupसमय अणु
	efi_bool_t	enabled;
	efi_समय_प्रकार	*समय;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_getnexthighmonotoniccount अणु
	u32		*high_count;
	efi_status_t	*status;
पूर्ण __packed;

काष्ठा efi_querycapsulecapabilities अणु
	efi_capsule_header_t	**capsule_header_array;
	अचिन्हित दीर्घ		capsule_count;
	u64			*maximum_capsule_size;
	पूर्णांक			*reset_type;
	efi_status_t		*status;
पूर्ण __packed;

काष्ठा efi_resetप्रणाली अणु
	पूर्णांक			reset_type;
	efi_status_t		status;
	अचिन्हित दीर्घ		data_size;
	efi_अक्षर16_t		*data;
पूर्ण __packed;

#घोषणा EFI_RUNTIME_GET_VARIABLE \
	_IOWR('p', 0x01, काष्ठा efi_getvariable)
#घोषणा EFI_RUNTIME_SET_VARIABLE \
	_IOW('p', 0x02, काष्ठा efi_setvariable)

#घोषणा EFI_RUNTIME_GET_TIME \
	_IOR('p', 0x03, काष्ठा efi_समय_लो)
#घोषणा EFI_RUNTIME_SET_TIME \
	_IOW('p', 0x04, काष्ठा efi_समय_रखो)

#घोषणा EFI_RUNTIME_GET_WAKETIME \
	_IOR('p', 0x05, काष्ठा efi_getwakeupसमय)
#घोषणा EFI_RUNTIME_SET_WAKETIME \
	_IOW('p', 0x06, काष्ठा efi_setwakeupसमय)

#घोषणा EFI_RUNTIME_GET_NEXTVARIABLENAME \
	_IOWR('p', 0x07, काष्ठा efi_getnextvariablename)

#घोषणा EFI_RUNTIME_QUERY_VARIABLEINFO \
	_IOR('p', 0x08, काष्ठा efi_queryvariableinfo)

#घोषणा EFI_RUNTIME_GET_NEXTHIGHMONOTONICCOUNT \
	_IOR('p', 0x09, काष्ठा efi_getnexthighmonotoniccount)

#घोषणा EFI_RUNTIME_QUERY_CAPSULECAPABILITIES \
	_IOR('p', 0x0A, काष्ठा efi_querycapsulecapabilities)

#घोषणा EFI_RUNTIME_RESET_SYSTEM \
	_IOW('p', 0x0B, काष्ठा efi_resetप्रणाली)

#घोषणा EFI_RUNTIME_GET_SUPPORTED_MASK \
	_IOR('p', 0x0C, अचिन्हित पूर्णांक)

#पूर्ण_अगर /* _DRIVERS_FIRMWARE_EFI_TEST_H_ */
