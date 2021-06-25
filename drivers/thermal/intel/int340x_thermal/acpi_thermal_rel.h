<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ACPI_ACPI_THERMAL_H
#घोषणा __ACPI_ACPI_THERMAL_H

#समावेश <यंत्र/ioctl.h>

#घोषणा ACPI_THERMAL_MAGIC 's'

#घोषणा ACPI_THERMAL_GET_TRT_LEN _IOR(ACPI_THERMAL_MAGIC, 1, अचिन्हित दीर्घ)
#घोषणा ACPI_THERMAL_GET_ART_LEN _IOR(ACPI_THERMAL_MAGIC, 2, अचिन्हित दीर्घ)
#घोषणा ACPI_THERMAL_GET_TRT_COUNT _IOR(ACPI_THERMAL_MAGIC, 3, अचिन्हित दीर्घ)
#घोषणा ACPI_THERMAL_GET_ART_COUNT _IOR(ACPI_THERMAL_MAGIC, 4, अचिन्हित दीर्घ)

#घोषणा ACPI_THERMAL_GET_TRT	_IOR(ACPI_THERMAL_MAGIC, 5, अचिन्हित दीर्घ)
#घोषणा ACPI_THERMAL_GET_ART	_IOR(ACPI_THERMAL_MAGIC, 6, अचिन्हित दीर्घ)

काष्ठा art अणु
	acpi_handle source;
	acpi_handle target;
	u64 weight;
	u64 ac0_max;
	u64 ac1_max;
	u64 ac2_max;
	u64 ac3_max;
	u64 ac4_max;
	u64 ac5_max;
	u64 ac6_max;
	u64 ac7_max;
	u64 ac8_max;
	u64 ac9_max;
पूर्ण __packed;

काष्ठा trt अणु
	acpi_handle source;
	acpi_handle target;
	u64 influence;
	u64 sample_period;
	u64 reserved1;
	u64 reserved2;
	u64 reserved3;
	u64 reserved4;
पूर्ण __packed;

#घोषणा ACPI_NR_ART_ELEMENTS 13
/* क्रम usrspace */
जोड़ art_object अणु
	काष्ठा अणु
		अक्षर source_device[8]; /* ACPI single name */
		अक्षर target_device[8]; /* ACPI single name */
		u64 weight;
		u64 ac0_max_level;
		u64 ac1_max_level;
		u64 ac2_max_level;
		u64 ac3_max_level;
		u64 ac4_max_level;
		u64 ac5_max_level;
		u64 ac6_max_level;
		u64 ac7_max_level;
		u64 ac8_max_level;
		u64 ac9_max_level;
	पूर्ण;
	u64 __data[ACPI_NR_ART_ELEMENTS];
पूर्ण;

जोड़ trt_object अणु
	काष्ठा अणु
		अक्षर source_device[8]; /* ACPI single name */
		अक्षर target_device[8]; /* ACPI single name */
		u64 influence;
		u64 sample_period;
		u64 reserved[4];
	पूर्ण;
	u64 __data[8];
पूर्ण;

#अगर_घोषित __KERNEL__
पूर्णांक acpi_thermal_rel_misc_device_add(acpi_handle handle);
पूर्णांक acpi_thermal_rel_misc_device_हटाओ(acpi_handle handle);
पूर्णांक acpi_parse_art(acpi_handle handle, पूर्णांक *art_count, काष्ठा art **arts,
		bool create_dev);
पूर्णांक acpi_parse_trt(acpi_handle handle, पूर्णांक *trt_count, काष्ठा trt **trts,
		bool create_dev);
#पूर्ण_अगर

#पूर्ण_अगर /* __ACPI_ACPI_THERMAL_H */
