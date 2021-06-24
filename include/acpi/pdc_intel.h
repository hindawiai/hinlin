<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* _PDC bit definition क्रम Intel processors */

#अगर_अघोषित __PDC_INTEL_H__
#घोषणा __PDC_INTEL_H__

#घोषणा ACPI_PDC_P_FFH			(0x0001)
#घोषणा ACPI_PDC_C_C1_HALT		(0x0002)
#घोषणा ACPI_PDC_T_FFH			(0x0004)
#घोषणा ACPI_PDC_SMP_C1PT		(0x0008)
#घोषणा ACPI_PDC_SMP_C2C3		(0x0010)
#घोषणा ACPI_PDC_SMP_P_SWCOORD		(0x0020)
#घोषणा ACPI_PDC_SMP_C_SWCOORD		(0x0040)
#घोषणा ACPI_PDC_SMP_T_SWCOORD		(0x0080)
#घोषणा ACPI_PDC_C_C1_FFH		(0x0100)
#घोषणा ACPI_PDC_C_C2C3_FFH		(0x0200)
#घोषणा ACPI_PDC_SMP_P_HWCOORD		(0x0800)

#घोषणा ACPI_PDC_EST_CAPABILITY_SMP	(ACPI_PDC_SMP_C1PT | \
					 ACPI_PDC_C_C1_HALT | \
					 ACPI_PDC_P_FFH)

#घोषणा ACPI_PDC_EST_CAPABILITY_SWSMP	(ACPI_PDC_SMP_C1PT | \
					 ACPI_PDC_C_C1_HALT | \
					 ACPI_PDC_SMP_P_SWCOORD | \
					 ACPI_PDC_SMP_P_HWCOORD | \
					 ACPI_PDC_P_FFH)

#घोषणा ACPI_PDC_C_CAPABILITY_SMP	(ACPI_PDC_SMP_C2C3  | \
					 ACPI_PDC_SMP_C1PT  | \
					 ACPI_PDC_C_C1_HALT | \
					 ACPI_PDC_C_C1_FFH  | \
					 ACPI_PDC_C_C2C3_FFH)

#पूर्ण_अगर				/* __PDC_INTEL_H__ */
