<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utglobal - Global variables क्रम the ACPI subप्रणाली
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES
#घोषणा DEFINE_ACPI_GLOBALS

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utglobal")

/*******************************************************************************
 *
 * Static global variable initialization.
 *
 ******************************************************************************/
/* Various state name strings */
स्थिर अक्षर *acpi_gbl_sleep_state_names[ACPI_S_STATE_COUNT] = अणु
	"\\_S0_",
	"\\_S1_",
	"\\_S2_",
	"\\_S3_",
	"\\_S4_",
	"\\_S5_"
पूर्ण;

स्थिर अक्षर *acpi_gbl_lowest_dstate_names[ACPI_NUM_sx_w_METHODS] = अणु
	"_S0W",
	"_S1W",
	"_S2W",
	"_S3W",
	"_S4W"
पूर्ण;

स्थिर अक्षर *acpi_gbl_highest_dstate_names[ACPI_NUM_sx_d_METHODS] = अणु
	"_S1D",
	"_S2D",
	"_S3D",
	"_S4D"
पूर्ण;

/* Hex-to-ascii */

स्थिर अक्षर acpi_gbl_lower_hex_digits[] = "0123456789abcdef";
स्थिर अक्षर acpi_gbl_upper_hex_digits[] = "0123456789ABCDEF";

/*******************************************************************************
 *
 * Namespace globals
 *
 ******************************************************************************/
/*
 * Predefined ACPI Names (Built-in to the Interpreter)
 *
 * NOTES:
 * 1) _SB_ is defined to be a device to allow \_SB_._INI to be run
 *    during the initialization sequence.
 * 2) _TZ_ is defined to be a thermal zone in order to allow ASL code to
 *    perक्रमm a Notअगरy() operation on it. 09/2010: Changed to type Device.
 *    This still allows notअगरies, but करोes not confuse host code that
 *    searches क्रम valid thermal_zone objects.
 */
स्थिर काष्ठा acpi_predefined_names acpi_gbl_pre_defined_names[] = अणु
	अणु"_GPE", ACPI_TYPE_LOCAL_SCOPE, शून्यपूर्ण,
	अणु"_PR_", ACPI_TYPE_LOCAL_SCOPE, शून्यपूर्ण,
	अणु"_SB_", ACPI_TYPE_DEVICE, शून्यपूर्ण,
	अणु"_SI_", ACPI_TYPE_LOCAL_SCOPE, शून्यपूर्ण,
	अणु"_TZ_", ACPI_TYPE_DEVICE, शून्यपूर्ण,
	/*
	 * March, 2015:
	 * The _REV object is in the process of being deprecated, because
	 * other ACPI implementations permanently वापस 2. Thus, it
	 * has little or no value. Return 2 क्रम compatibility with
	 * other ACPI implementations.
	 */
	अणु"_REV", ACPI_TYPE_INTEGER, ACPI_CAST_PTR(अक्षर, 2)पूर्ण,
	अणु"_OS_", ACPI_TYPE_STRING, ACPI_OS_NAMEपूर्ण,
	अणु"_GL_", ACPI_TYPE_MUTEX, ACPI_CAST_PTR(अक्षर, 1)पूर्ण,
	अणु"_OSI", ACPI_TYPE_METHOD, ACPI_CAST_PTR(अक्षर, 1)पूर्ण,

	/* Table terminator */

	अणुशून्य, ACPI_TYPE_ANY, शून्यपूर्ण
पूर्ण;

#अगर (!ACPI_REDUCED_HARDWARE)
/******************************************************************************
 *
 * Event and Hardware globals
 *
 ******************************************************************************/

काष्ठा acpi_bit_रेजिस्टर_info acpi_gbl_bit_रेजिस्टर_info[ACPI_NUM_BITREG] = अणु
	/* Name                                     Parent Register             Register Bit Position                   Register Bit Mask       */

	/* ACPI_BITREG_TIMER_STATUS         */ अणुACPI_REGISTER_PM1_STATUS,
						ACPI_BITPOSITION_TIMER_STATUS,
						ACPI_BITMASK_TIMER_STATUSपूर्ण,
	/* ACPI_BITREG_BUS_MASTER_STATUS    */ अणुACPI_REGISTER_PM1_STATUS,
						ACPI_BITPOSITION_BUS_MASTER_STATUS,
						ACPI_BITMASK_BUS_MASTER_STATUSपूर्ण,
	/* ACPI_BITREG_GLOBAL_LOCK_STATUS   */ अणुACPI_REGISTER_PM1_STATUS,
						ACPI_BITPOSITION_GLOBAL_LOCK_STATUS,
						ACPI_BITMASK_GLOBAL_LOCK_STATUSपूर्ण,
	/* ACPI_BITREG_POWER_BUTTON_STATUS  */ अणुACPI_REGISTER_PM1_STATUS,
						ACPI_BITPOSITION_POWER_BUTTON_STATUS,
						ACPI_BITMASK_POWER_BUTTON_STATUSपूर्ण,
	/* ACPI_BITREG_SLEEP_BUTTON_STATUS  */ अणुACPI_REGISTER_PM1_STATUS,
						ACPI_BITPOSITION_SLEEP_BUTTON_STATUS,
						ACPI_BITMASK_SLEEP_BUTTON_STATUSपूर्ण,
	/* ACPI_BITREG_RT_CLOCK_STATUS      */ अणुACPI_REGISTER_PM1_STATUS,
						ACPI_BITPOSITION_RT_CLOCK_STATUS,
						ACPI_BITMASK_RT_CLOCK_STATUSपूर्ण,
	/* ACPI_BITREG_WAKE_STATUS          */ अणुACPI_REGISTER_PM1_STATUS,
						ACPI_BITPOSITION_WAKE_STATUS,
						ACPI_BITMASK_WAKE_STATUSपूर्ण,
	/* ACPI_BITREG_PCIEXP_WAKE_STATUS   */ अणुACPI_REGISTER_PM1_STATUS,
						ACPI_BITPOSITION_PCIEXP_WAKE_STATUS,
						ACPI_BITMASK_PCIEXP_WAKE_STATUSपूर्ण,

	/* ACPI_BITREG_TIMER_ENABLE         */ अणुACPI_REGISTER_PM1_ENABLE,
						ACPI_BITPOSITION_TIMER_ENABLE,
						ACPI_BITMASK_TIMER_ENABLEपूर्ण,
	/* ACPI_BITREG_GLOBAL_LOCK_ENABLE   */ अणुACPI_REGISTER_PM1_ENABLE,
						ACPI_BITPOSITION_GLOBAL_LOCK_ENABLE,
						ACPI_BITMASK_GLOBAL_LOCK_ENABLEपूर्ण,
	/* ACPI_BITREG_POWER_BUTTON_ENABLE  */ अणुACPI_REGISTER_PM1_ENABLE,
						ACPI_BITPOSITION_POWER_BUTTON_ENABLE,
						ACPI_BITMASK_POWER_BUTTON_ENABLEपूर्ण,
	/* ACPI_BITREG_SLEEP_BUTTON_ENABLE  */ अणुACPI_REGISTER_PM1_ENABLE,
						ACPI_BITPOSITION_SLEEP_BUTTON_ENABLE,
						ACPI_BITMASK_SLEEP_BUTTON_ENABLEपूर्ण,
	/* ACPI_BITREG_RT_CLOCK_ENABLE      */ अणुACPI_REGISTER_PM1_ENABLE,
						ACPI_BITPOSITION_RT_CLOCK_ENABLE,
						ACPI_BITMASK_RT_CLOCK_ENABLEपूर्ण,
	/* ACPI_BITREG_PCIEXP_WAKE_DISABLE  */ अणुACPI_REGISTER_PM1_ENABLE,
						ACPI_BITPOSITION_PCIEXP_WAKE_DISABLE,
						ACPI_BITMASK_PCIEXP_WAKE_DISABLEपूर्ण,

	/* ACPI_BITREG_SCI_ENABLE           */ अणुACPI_REGISTER_PM1_CONTROL,
						ACPI_BITPOSITION_SCI_ENABLE,
						ACPI_BITMASK_SCI_ENABLEपूर्ण,
	/* ACPI_BITREG_BUS_MASTER_RLD       */ अणुACPI_REGISTER_PM1_CONTROL,
						ACPI_BITPOSITION_BUS_MASTER_RLD,
						ACPI_BITMASK_BUS_MASTER_RLDपूर्ण,
	/* ACPI_BITREG_GLOBAL_LOCK_RELEASE  */ अणुACPI_REGISTER_PM1_CONTROL,
						ACPI_BITPOSITION_GLOBAL_LOCK_RELEASE,
						ACPI_BITMASK_GLOBAL_LOCK_RELEASEपूर्ण,
	/* ACPI_BITREG_SLEEP_TYPE           */ अणुACPI_REGISTER_PM1_CONTROL,
						ACPI_BITPOSITION_SLEEP_TYPE,
						ACPI_BITMASK_SLEEP_TYPEपूर्ण,
	/* ACPI_BITREG_SLEEP_ENABLE         */ अणुACPI_REGISTER_PM1_CONTROL,
						ACPI_BITPOSITION_SLEEP_ENABLE,
						ACPI_BITMASK_SLEEP_ENABLEपूर्ण,

	/* ACPI_BITREG_ARB_DIS              */ अणुACPI_REGISTER_PM2_CONTROL,
						ACPI_BITPOSITION_ARB_DISABLE,
						ACPI_BITMASK_ARB_DISABLEपूर्ण
पूर्ण;

काष्ठा acpi_fixed_event_info acpi_gbl_fixed_event_info[ACPI_NUM_FIXED_EVENTS] = अणु
	/* ACPI_EVENT_PMTIMER       */ अणुACPI_BITREG_TIMER_STATUS,
					ACPI_BITREG_TIMER_ENABLE,
					ACPI_BITMASK_TIMER_STATUS,
					ACPI_BITMASK_TIMER_ENABLEपूर्ण,
	/* ACPI_EVENT_GLOBAL        */ अणुACPI_BITREG_GLOBAL_LOCK_STATUS,
					ACPI_BITREG_GLOBAL_LOCK_ENABLE,
					ACPI_BITMASK_GLOBAL_LOCK_STATUS,
					ACPI_BITMASK_GLOBAL_LOCK_ENABLEपूर्ण,
	/* ACPI_EVENT_POWER_BUTTON  */ अणुACPI_BITREG_POWER_BUTTON_STATUS,
					ACPI_BITREG_POWER_BUTTON_ENABLE,
					ACPI_BITMASK_POWER_BUTTON_STATUS,
					ACPI_BITMASK_POWER_BUTTON_ENABLEपूर्ण,
	/* ACPI_EVENT_SLEEP_BUTTON  */ अणुACPI_BITREG_SLEEP_BUTTON_STATUS,
					ACPI_BITREG_SLEEP_BUTTON_ENABLE,
					ACPI_BITMASK_SLEEP_BUTTON_STATUS,
					ACPI_BITMASK_SLEEP_BUTTON_ENABLEपूर्ण,
	/* ACPI_EVENT_RTC           */ अणुACPI_BITREG_RT_CLOCK_STATUS,
					ACPI_BITREG_RT_CLOCK_ENABLE,
					ACPI_BITMASK_RT_CLOCK_STATUS,
					ACPI_BITMASK_RT_CLOCK_ENABLEपूर्ण,
पूर्ण;
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

#अगर defined (ACPI_DISASSEMBLER) || defined (ACPI_ASL_COMPILER)

/* to_pld macro: compile/disassemble strings */

स्थिर अक्षर *acpi_gbl_pld_panel_list[] = अणु
	"TOP",
	"BOTTOM",
	"LEFT",
	"RIGHT",
	"FRONT",
	"BACK",
	"UNKNOWN",
	शून्य
पूर्ण;

स्थिर अक्षर *acpi_gbl_pld_vertical_position_list[] = अणु
	"UPPER",
	"CENTER",
	"LOWER",
	शून्य
पूर्ण;

स्थिर अक्षर *acpi_gbl_pld_horizontal_position_list[] = अणु
	"LEFT",
	"CENTER",
	"RIGHT",
	शून्य
पूर्ण;

स्थिर अक्षर *acpi_gbl_pld_shape_list[] = अणु
	"ROUND",
	"OVAL",
	"SQUARE",
	"VERTICALRECTANGLE",
	"HORIZONTALRECTANGLE",
	"VERTICALTRAPEZOID",
	"HORIZONTALTRAPEZOID",
	"UNKNOWN",
	"CHAMFERED",
	शून्य
पूर्ण;
#पूर्ण_अगर

/* Public globals */

ACPI_EXPORT_SYMBOL(acpi_gbl_FADT)
ACPI_EXPORT_SYMBOL(acpi_dbg_level)
ACPI_EXPORT_SYMBOL(acpi_dbg_layer)
ACPI_EXPORT_SYMBOL(acpi_gpe_count)
ACPI_EXPORT_SYMBOL(acpi_current_gpe_count)
