<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Name: hwसमयr.c - ACPI Power Management Timer Interface
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwtimer")

#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/******************************************************************************
 *
 * FUNCTION:    acpi_get_समयr_resolution
 *
 * PARAMETERS:  resolution          - Where the resolution is वापसed
 *
 * RETURN:      Status and समयr resolution
 *
 * DESCRIPTION: Obtains resolution of the ACPI PM Timer (24 or 32 bits).
 *
 ******************************************************************************/
acpi_status acpi_get_समयr_resolution(u32 * resolution)
अणु
	ACPI_FUNCTION_TRACE(acpi_get_समयr_resolution);

	अगर (!resolution) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर ((acpi_gbl_FADT.flags & ACPI_FADT_32BIT_TIMER) == 0) अणु
		*resolution = 24;
	पूर्ण अन्यथा अणु
		*resolution = 32;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_समयr_resolution)

/******************************************************************************
 *
 * FUNCTION:    acpi_get_समयr
 *
 * PARAMETERS:  ticks               - Where the समयr value is वापसed
 *
 * RETURN:      Status and current समयr value (ticks)
 *
 * DESCRIPTION: Obtains current value of ACPI PM Timer (in ticks).
 *
 ******************************************************************************/
acpi_status acpi_get_समयr(u32 * ticks)
अणु
	acpi_status status;
	u64 समयr_value;

	ACPI_FUNCTION_TRACE(acpi_get_समयr);

	अगर (!ticks) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* ACPI 5.0A: PM Timer is optional */

	अगर (!acpi_gbl_FADT.xpm_समयr_block.address) अणु
		वापस_ACPI_STATUS(AE_SUPPORT);
	पूर्ण

	status = acpi_hw_पढ़ो(&समयr_value, &acpi_gbl_FADT.xpm_समयr_block);
	अगर (ACPI_SUCCESS(status)) अणु

		/* ACPI PM Timer is defined to be 32 bits (PM_TMR_LEN) */

		*ticks = (u32)समयr_value;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_समयr)

/******************************************************************************
 *
 * FUNCTION:    acpi_get_समयr_duration
 *
 * PARAMETERS:  start_ticks         - Starting बारtamp
 *              end_ticks           - End बारtamp
 *              समय_elapsed        - Where the elapsed समय is वापसed
 *
 * RETURN:      Status and समय_elapsed
 *
 * DESCRIPTION: Computes the समय elapsed (in microseconds) between two
 *              PM Timer समय stamps, taking पूर्णांकo account the possibility of
 *              rollovers, the समयr resolution, and समयr frequency.
 *
 *              The PM Timer's घड़ी ticks at roughly 3.6 बार per
 *              _microsecond_, and its घड़ी जारीs through Cx state
 *              transitions (unlike many CPU बारtamp counters) -- making it
 *              a versatile and accurate समयr.
 *
 *              Note that this function accommodates only a single समयr
 *              rollover. Thus क्रम 24-bit समयrs, this function should only
 *              be used क्रम calculating durations less than ~4.6 seconds
 *              (~20 minutes क्रम 32-bit समयrs) -- calculations below:
 *
 *              2**24 Ticks / 3,600,000 Ticks/Sec = 4.66 sec
 *              2**32 Ticks / 3,600,000 Ticks/Sec = 1193 sec or 19.88 minutes
 *
 ******************************************************************************/
acpi_status
acpi_get_समयr_duration(u32 start_ticks, u32 end_ticks, u32 *समय_elapsed)
अणु
	acpi_status status;
	u64 delta_ticks;
	u64 quotient;

	ACPI_FUNCTION_TRACE(acpi_get_समयr_duration);

	अगर (!समय_elapsed) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* ACPI 5.0A: PM Timer is optional */

	अगर (!acpi_gbl_FADT.xpm_समयr_block.address) अणु
		वापस_ACPI_STATUS(AE_SUPPORT);
	पूर्ण

	अगर (start_ticks == end_ticks) अणु
		*समय_elapsed = 0;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Compute Tick Delta:
	 * Handle (max one) समयr rollovers on 24-bit versus 32-bit समयrs.
	 */
	delta_ticks = end_ticks;
	अगर (start_ticks > end_ticks) अणु
		अगर ((acpi_gbl_FADT.flags & ACPI_FADT_32BIT_TIMER) == 0) अणु

			/* 24-bit Timer */

			delta_ticks |= (u64)1 << 24;
		पूर्ण अन्यथा अणु
			/* 32-bit Timer */

			delta_ticks |= (u64)1 << 32;
		पूर्ण
	पूर्ण
	delta_ticks -= start_ticks;

	/*
	 * Compute Duration (Requires a 64-bit multiply and भागide):
	 *
	 * समय_elapsed (microseconds) =
	 *  (delta_ticks * ACPI_USEC_PER_SEC) / ACPI_PM_TIMER_FREQUENCY;
	 */
	status = acpi_ut_लघु_भागide(delta_ticks * ACPI_USEC_PER_SEC,
				      ACPI_PM_TIMER_FREQUENCY, &quotient, शून्य);

	*समय_elapsed = (u32)quotient;
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_समयr_duration)
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
