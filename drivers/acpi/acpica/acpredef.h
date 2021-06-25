<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acpredef - Inक्रमmation table क्रम ACPI predefined methods and objects
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACPREDEF_H__
#घोषणा __ACPREDEF_H__

/******************************************************************************
 *
 * Return Package types
 *
 * 1) PTYPE1 packages करो not contain subpackages.
 *
 * ACPI_PTYPE1_FIXED: Fixed-length length, 1 or 2 object types:
 *      object type
 *      count
 *      object type
 *      count
 *
 * ACPI_PTYPE1_VAR: Variable-length length. Zero-length package is allowed:
 *      object type (Int/Buf/Ref)
 *
 * ACPI_PTYPE1_OPTION: Package has some required and some optional elements
 *      (Used क्रम _PRW)
 *
 *
 * 2) PTYPE2 packages contain a Variable-length number of subpackages. Each
 *    of the dअगरferent types describe the contents of each of the subpackages.
 *
 * ACPI_PTYPE2: Each subpackage contains 1 or 2 object types. Zero-length
 *      parent package is allowed:
 *      object type
 *      count
 *      object type
 *      count
 *      (Used क्रम _ALR,_MLS,_PSS,_TRT,_TSS)
 *
 * ACPI_PTYPE2_COUNT: Each subpackage has a count as first element.
 *      Zero-length parent package is allowed:
 *      object type
 *      (Used क्रम _CSD,_PSD,_TSD)
 *
 * ACPI_PTYPE2_PKG_COUNT: Count of subpackages at start, 1 or 2 object types:
 *      object type
 *      count
 *      object type
 *      count
 *      (Used क्रम _CST)
 *
 * ACPI_PTYPE2_FIXED: Each subpackage is of Fixed-length. Zero-length
 *      parent package is allowed.
 *      (Used क्रम _PRT)
 *
 * ACPI_PTYPE2_MIN: Each subpackage has a Variable-length but minimum length.
 *      Zero-length parent package is allowed:
 *      (Used क्रम _HPX)
 *
 * ACPI_PTYPE2_REV_FIXED: Revision at start, each subpackage is Fixed-length
 *      (Used क्रम _ART, _FPS)
 *
 * ACPI_PTYPE2_FIX_VAR: Each subpackage consists of some fixed-length elements
 *      followed by an optional element. Zero-length parent package is allowed.
 *      object type
 *      count
 *      object type
 *      count = 0 (optional)
 *      (Used क्रम _DLM)
 *
 * ACPI_PTYPE2_VAR_VAR: Variable number of subpackages, each of either a
 *      स्थिरant or variable length. The subpackages are preceded by a
 *      स्थिरant number of objects.
 *      (Used क्रम _LPI, _RDI)
 *
 * ACPI_PTYPE2_UUID_PAIR: Each subpackage is preceded by a UUID Buffer. The UUID
 *      defines the क्रमmat of the package. Zero-length parent package is
 *      allowed.
 *      (Used क्रम _DSD)
 *
 *****************************************************************************/

क्रमागत acpi_वापस_package_types अणु
	ACPI_PTYPE1_FIXED = 1,
	ACPI_PTYPE1_VAR = 2,
	ACPI_PTYPE1_OPTION = 3,
	ACPI_PTYPE2 = 4,
	ACPI_PTYPE2_COUNT = 5,
	ACPI_PTYPE2_PKG_COUNT = 6,
	ACPI_PTYPE2_FIXED = 7,
	ACPI_PTYPE2_MIN = 8,
	ACPI_PTYPE2_REV_FIXED = 9,
	ACPI_PTYPE2_FIX_VAR = 10,
	ACPI_PTYPE2_VAR_VAR = 11,
	ACPI_PTYPE2_UUID_PAIR = 12,
	ACPI_PTYPE_CUSTOM = 13
पूर्ण;

/* Support macros क्रम users of the predefined info table */

#घोषणा METHOD_PREDEF_ARGS_MAX          5
#घोषणा METHOD_ARG_BIT_WIDTH            3
#घोषणा METHOD_ARG_MASK                 0x0007
#घोषणा ARG_COUNT_IS_MINIMUM            0x8000
#घोषणा METHOD_MAX_ARG_TYPE             ACPI_TYPE_PACKAGE

#घोषणा METHOD_GET_ARG_COUNT(arg_list)  ((arg_list) & METHOD_ARG_MASK)
#घोषणा METHOD_GET_NEXT_TYPE(arg_list)  (((arg_list) >>= METHOD_ARG_BIT_WIDTH) & METHOD_ARG_MASK)

/* Macros used to build the predefined info table */

#घोषणा METHOD_0ARGS                    0
#घोषणा METHOD_1ARGS(a1)                (1 | (a1 << 3))
#घोषणा METHOD_2ARGS(a1,a2)             (2 | (a1 << 3) | (a2 << 6))
#घोषणा METHOD_3ARGS(a1,a2,a3)          (3 | (a1 << 3) | (a2 << 6) | (a3 << 9))
#घोषणा METHOD_4ARGS(a1,a2,a3,a4)       (4 | (a1 << 3) | (a2 << 6) | (a3 << 9) | (a4 << 12))
#घोषणा METHOD_5ARGS(a1,a2,a3,a4,a5)    (5 | (a1 << 3) | (a2 << 6) | (a3 << 9) | (a4 << 12) | (a5 << 15))

#घोषणा METHOD_RETURNS(type)            (type)
#घोषणा METHOD_NO_RETURN_VALUE          0

#घोषणा PACKAGE_INFO(a,b,c,d,e,f)       अणुअणुअणु(a),(b),(c),(d)पूर्ण, ((((u16)(f)) << 8) | (e)), 0पूर्णपूर्ण

/* Support macros क्रम the resource descriptor info table */

#घोषणा WIDTH_1                         0x0001
#घोषणा WIDTH_2                         0x0002
#घोषणा WIDTH_3                         0x0004
#घोषणा WIDTH_8                         0x0008
#घोषणा WIDTH_16                        0x0010
#घोषणा WIDTH_32                        0x0020
#घोषणा WIDTH_64                        0x0040
#घोषणा VARIABLE_DATA                   0x0080
#घोषणा NUM_RESOURCE_WIDTHS             8

#घोषणा WIDTH_ADDRESS                   WIDTH_16 | WIDTH_32 | WIDTH_64

#अगर_घोषित ACPI_CREATE_PREDEFINED_TABLE
/******************************************************************************
 *
 * Predefined method/object inक्रमmation table.
 *
 * These are the names that can actually be evaluated via acpi_evaluate_object.
 * Not present in this table are the following:
 *
 *      1) Predefined/Reserved names that are not usually evaluated via
 *         acpi_evaluate_object:
 *              _Lxx and _Exx GPE methods
 *              _Qxx EC methods
 *              _T_x compiler temporary variables
 *              _Wxx wake events
 *
 *      2) Predefined names that never actually exist within the AML code:
 *              Predefined resource descriptor field names
 *
 *      3) Predefined names that are implemented within ACPICA:
 *              _OSI
 *
 * The मुख्य entries in the table each contain the following items:
 *
 * name                 - The ACPI reserved name
 * argument_list        - Contains (in 16 bits), the number of required
 *                        arguments to the method (3 bits), and a 3-bit type
 *                        field क्रम each argument (up to 4 arguments). The
 *                        METHOD_?ARGS macros generate the correct packed data.
 * expected_btypes      - Allowed type(s) क्रम the वापस value.
 *                        0 means that no वापस value is expected.
 *
 * For methods that वापस packages, the next entry in the table contains
 * inक्रमmation about the expected काष्ठाure of the package. This inक्रमmation
 * is saved here (rather than in a separate table) in order to minimize the
 * overall size of the stored data.
 *
 * Note: The additional braces are पूर्णांकended to promote portability.
 *
 * Note2: Table is used by the kernel-resident subप्रणाली, the iASL compiler,
 * and the acpi_help utility.
 *
 * TBD: _PRT - currently ignore reversed entries. Attempt to fix in nsrepair.
 * Possibly fixing package elements like _BIF, etc.
 *
 *****************************************************************************/

स्थिर जोड़ acpi_predefined_info acpi_gbl_predefined_methods[] = अणु
	अणुअणु"_AC0", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC1", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC2", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC3", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC4", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC5", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC6", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC7", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC8", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AC9", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_ADR", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_AEI", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_AL0", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL1", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL2", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL3", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL4", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL5", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL6", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL7", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL8", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_AL9", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_ALC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_ALI", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_ALP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_ALR", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each 2 (Ints) */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_RTYPE_INTEGER, 2, 0, 0, 0),

	अणुअणु"_ALT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_ART", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (1 Int(rev), n Pkg (2 Ref/11 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_REV_FIXED, ACPI_RTYPE_REFERENCE, 2,
		     ACPI_RTYPE_INTEGER, 11, 0),

	अणुअणु"_BBN", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_BCL", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Ints) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 0, 0, 0, 0),

	अणुअणु"_BCM", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_BCT", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_BDN", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_BFS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_BIF", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (9 Int),(4 Str) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 9,
		     ACPI_RTYPE_STRING, 4, 0),

	अणुअणु"_BIX", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (16 Int),(4 Str) */
	PACKAGE_INFO(ACPI_PTYPE_CUSTOM, ACPI_RTYPE_INTEGER, 16,
		     ACPI_RTYPE_STRING, 4, 0),

	अणुअणु"_BLT",
	  METHOD_3ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_BMA", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_BMC", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_BMD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (5 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 5, 0, 0, 0),

	अणुअणु"_BMS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_BPC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4, 0, 0, 0),

	अणुअणु"_BPS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (5 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 5, 0, 0, 0),

	अणुअणु"_BPT", METHOD_1ARGS(ACPI_TYPE_PACKAGE),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_BQC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_BST", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4, 0, 0, 0),

	अणुअणु"_BTH", METHOD_1ARGS(ACPI_TYPE_INTEGER),	/* ACPI 6.0 */
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_BTM", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_BTP", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_CBA", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* See PCI firmware spec 3.0 */

	अणुअणु"_CBR", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (3 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 3, 0, 0, 0),

	अणुअणु"_CCA", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* ACPI 5.1 */

	अणुअणु"_CDM", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_CID", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING | ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Ints/Strs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING, 0,
		     0, 0, 0),

	अणुअणु"_CLS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (3 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 3, 0, 0, 0),

	अणुअणु"_CPC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Ints/Bufs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER | ACPI_RTYPE_BUFFER, 0,
		     0, 0, 0),

	अणुअणु"_CR3", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_CRS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_CRT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_CSD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (1 Int(n), n-1 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_COUNT, ACPI_RTYPE_INTEGER, 0, 0, 0, 0),

	अणुअणु"_CST", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (1 Int(n), n Pkg (1 Buf/3 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_PKG_COUNT, ACPI_RTYPE_BUFFER, 1,
		     ACPI_RTYPE_INTEGER, 3, 0),

	अणुअणु"_CWS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_DCK", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_DCS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_DDC", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER | ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_DDN", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_STRING)पूर्णपूर्ण,

	अणुअणु"_DEP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_DGS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_DIS", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_DLM", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each (1 Ref, 0/1 Optional Buf/Ref) */
	PACKAGE_INFO(ACPI_PTYPE2_FIX_VAR, ACPI_RTYPE_REFERENCE, 1,
		     ACPI_RTYPE_REFERENCE | ACPI_RTYPE_BUFFER, 0, 0),

	अणुअणु"_DMA", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_DOD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Ints) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 0, 0, 0, 0),

	अणुअणु"_DOS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_DSD", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each: 1 Buf, 1 Pkg */
	PACKAGE_INFO(ACPI_PTYPE2_UUID_PAIR, ACPI_RTYPE_BUFFER, 1,
		     ACPI_RTYPE_PACKAGE, 1, 0),

	अणुअणु"_DSM",
	  METHOD_4ARGS(ACPI_TYPE_BUFFER, ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER,
		       ACPI_TYPE_PACKAGE),
	  METHOD_RETURNS(ACPI_RTYPE_ALL)पूर्णपूर्ण,	/* Must वापस a value, but it can be of any type */

	अणुअणु"_DSS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_DSW",
	  METHOD_3ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_DTI", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_EC_", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_EDL", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_EJ0", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_EJ1", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_EJ2", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_EJ3", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_EJ4", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_EJD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_STRING)पूर्णपूर्ण,

	अणुअणु"_ERR",
	  METHOD_3ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_STRING, ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* Internal use only, used by ACPICA test suites */

	अणुअणु"_EVT", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_FDE", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_FDI", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (16 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 16, 0, 0, 0),

	अणुअणु"_FDM", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_FIF", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4, 0, 0, 0),

	अणुअणु"_FIT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,	/* ACPI 6.0 */

	अणुअणु"_FIX", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Ints) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 0, 0, 0, 0),

	अणुअणु"_FPS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (1 Int(rev), n Pkg (5 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_REV_FIXED, ACPI_RTYPE_INTEGER, 5, 0, 0, 0),

	अणुअणु"_FSL", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_FST", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (3 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 3, 0, 0, 0),

	अणुअणु"_GAI", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_GCP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_GHL", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_GLK", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_GPD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_GPE", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* _GPE method, not _GPE scope */

	अणुअणु"_GRT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_GSB", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_GTF", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_GTM", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_GTS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_GWS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_HID", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING)पूर्णपूर्ण,

	अणुअणु"_HMA", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_HOT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_HPP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4, 0, 0, 0),

	/*
	 * For _HPX, a single package is वापसed, containing a variable-length number
	 * of subpackages. Each subpackage contains a PCI record setting.
	 * There are several dअगरferent type of record settings, of dअगरferent
	 * lengths, but all elements of all settings are Integers.
	 */
	अणुअणु"_HPX", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each (var Ints) */
	PACKAGE_INFO(ACPI_PTYPE2_MIN, ACPI_RTYPE_INTEGER, 5, 0, 0, 0),

	अणुअणु"_HRV", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_IFT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* See IPMI spec */

	अणुअणु"_INI", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_IRC", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_LCK", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_LID", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_LPD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (1 Int(rev), n Pkg (2 Int) */
	PACKAGE_INFO(ACPI_PTYPE2_REV_FIXED, ACPI_RTYPE_INTEGER, 2, 0, 0, 0),

	अणुअणु"_LPI", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (3 Int, n Pkg (10 Int/Buf) */
	PACKAGE_INFO(ACPI_PTYPE2_VAR_VAR, ACPI_RTYPE_INTEGER, 3,
		     ACPI_RTYPE_INTEGER | ACPI_RTYPE_BUFFER | ACPI_RTYPE_STRING,
		     10, 0),

	अणुअणु"_LSI", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 3, 0, 0, 0),

	अणुअणु"_LSR", METHOD_2ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 1,
		     ACPI_RTYPE_BUFFER, 1, 0),

	अणुअणु"_LSW",
	  METHOD_3ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER, ACPI_TYPE_BUFFER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_MAT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_MBM", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (8 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 8, 0, 0, 0),

	अणुअणु"_MLS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each (1 Str/1 Buf) */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_RTYPE_STRING, 1, ACPI_RTYPE_BUFFER, 1,
		     0),

	अणुअणु"_MSG", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_MSM",
	  METHOD_4ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER,
		       ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_MTL", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_NBS", METHOD_0ARGS,	/* ACPI 6.3 */
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_NCH", METHOD_0ARGS,	/* ACPI 6.3 */
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_NIC", METHOD_0ARGS,	/* ACPI 6.3 */
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_NIG", METHOD_0ARGS, /* ACPI 6.3 */
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_NIH", METHOD_1ARGS(ACPI_TYPE_BUFFER), /* ACPI 6.3 */
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_NTT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_OFF", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_ON_", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_OS_", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_STRING)पूर्णपूर्ण,

	अणुअणु"_OSC",
	  METHOD_4ARGS(ACPI_TYPE_BUFFER, ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER,
		       ACPI_TYPE_BUFFER),
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_OST",
	  METHOD_3ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER, ACPI_TYPE_BUFFER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PAI", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_PCL", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PCT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (2 Buf) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_BUFFER, 2, 0, 0, 0),

	अणुअणु"_PDC", METHOD_1ARGS(ACPI_TYPE_BUFFER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PDL", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_PIC", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PIF", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (3 Int),(3 Str) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 3,
		     ACPI_RTYPE_STRING, 3, 0),

	अणुअणु"_PLD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Bufs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_BUFFER, 0, 0, 0, 0),

	अणुअणु"_PMC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (11 Int),(3 Str) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 11,
		     ACPI_RTYPE_STRING, 3, 0),

	अणुअणु"_PMD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PMM", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_PPC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_PPE", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* See dig64 spec */

	अणुअणु"_PR0", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PR1", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PR2", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PR3", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PRE", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PRL", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PRR", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (1 Ref) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_REFERENCE, 1, 0, 0, 0),

	अणुअणु"_PRS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	/*
	 * For _PRT, many BIOSs reverse the 3rd and 4th Package elements (Source
	 * and source_index). This bug is so prevalent that there is code in the
	 * ACPICA Resource Manager to detect this and चयन them back. For now,
	 * करो not allow and issue a warning. To allow this and eliminate the
	 * warning, add the ACPI_RTYPE_REFERENCE type to the 4th element (index 3)
	 * in the statement below.
	 */
	अणुअणु"_PRT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each (4): Int,Int,Int/Ref,Int */
	PACKAGE_INFO(ACPI_PTYPE2_FIXED, 4, ACPI_RTYPE_INTEGER,
		     ACPI_RTYPE_INTEGER,
		     ACPI_RTYPE_INTEGER | ACPI_RTYPE_REFERENCE,
		     ACPI_RTYPE_INTEGER),

	अणुअणु"_PRW", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each: Pkg/Int,Int,[Variable-length Refs] (Pkg is Ref/Int) */
	PACKAGE_INFO(ACPI_PTYPE1_OPTION, 2,
		     ACPI_RTYPE_INTEGER | ACPI_RTYPE_PACKAGE,
		     ACPI_RTYPE_INTEGER, ACPI_RTYPE_REFERENCE, 0),

	अणुअणु"_PS0", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PS1", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PS2", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PS3", METHOD_0ARGS,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PSC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_PSD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each (5 Int) with count */
	PACKAGE_INFO(ACPI_PTYPE2_COUNT, ACPI_RTYPE_INTEGER, 0, 0, 0, 0),

	अणुअणु"_PSE", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PSL", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_PSR", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_PSS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each (6 Int) */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_RTYPE_INTEGER, 6, 0, 0, 0),

	अणुअणु"_PSV", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_PSW", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PTC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (2 Buf) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_BUFFER, 2, 0, 0, 0),

	अणुअणु"_PTP", METHOD_2ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_PTS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_PUR", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (2 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 2, 0, 0, 0),

	अणुअणु"_PXM", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_RDI", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (1 Int, n Pkg (m Ref)) */
	PACKAGE_INFO(ACPI_PTYPE2_VAR_VAR, ACPI_RTYPE_INTEGER, 1,
		     ACPI_RTYPE_REFERENCE, 0, 0),

	अणुअणु"_REG", METHOD_2ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_REV", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_RMV", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_ROM", METHOD_2ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_RST", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_RTV", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	/*
	 * For _S0_ through _S5_, the ACPI spec defines a वापस Package
	 * containing 1 Integer, but most DSDTs have it wrong - 2,3, or 4 पूर्णांकegers.
	 * Allow this by making the objects "Variable-length length", but all elements
	 * must be Integers.
	 */
	अणुअणु"_S0_", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1, 0, 0, 0),

	अणुअणु"_S1_", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1, 0, 0, 0),

	अणुअणु"_S2_", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1, 0, 0, 0),

	अणुअणु"_S3_", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1, 0, 0, 0),

	अणुअणु"_S4_", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1, 0, 0, 0),

	अणुअणु"_S5_", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (1 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1, 0, 0, 0),

	अणुअणु"_S1D", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_S2D", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_S3D", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_S4D", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_S0W", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_S1W", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_S2W", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_S3W", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_S4W", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_SBA", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4, 0, 0, 0),

	अणुअणु"_SBI", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (1 Int, 1 Buf) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 1,
		     ACPI_RTYPE_BUFFER, 1, 0),

	अणुअणु"_SBR",
	  METHOD_3ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER,
			ACPI_TYPE_INTEGER),
	   METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (2 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 2,
		     ACPI_RTYPE_BUFFER | ACPI_RTYPE_INTEGER, 1, 0),

	अणुअणु"_SBS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_SBT",
	  METHOD_4ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER,
			ACPI_TYPE_ANY),
	   METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (2 Int, 1 Buf | Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 2,
		     ACPI_RTYPE_BUFFER | ACPI_RTYPE_INTEGER, 1, 0),

	अणुअणु"_SBW",
	  METHOD_5ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER,
			ACPI_TYPE_INTEGER, ACPI_TYPE_ANY),
	   METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_BUFFER | ACPI_RTYPE_INTEGER,
		     1, 0, 0, 0),

	अणुअणु"_SCP", METHOD_1ARGS(ACPI_TYPE_INTEGER) | ARG_COUNT_IS_MINIMUM,
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,	/* Acpi 1.0 allowed 1 पूर्णांकeger arg. Acpi 3.0 expanded to 3 args. Allow both. */

	अणुअणु"_SDD", METHOD_1ARGS(ACPI_TYPE_BUFFER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_SEG", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_SHL", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_SLI", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_SPD", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_SRS", METHOD_1ARGS(ACPI_TYPE_BUFFER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_SRT", METHOD_1ARGS(ACPI_TYPE_BUFFER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_SRV", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* See IPMI spec */

	अणुअणु"_SST", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_STA", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_STM",
	  METHOD_3ARGS(ACPI_TYPE_BUFFER, ACPI_TYPE_BUFFER, ACPI_TYPE_BUFFER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_STP", METHOD_2ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_STR", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_STV", METHOD_2ARGS(ACPI_TYPE_INTEGER, ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_SUB", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_STRING)पूर्णपूर्ण,

	अणुअणु"_SUN", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_SWS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TC1", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TC2", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TDL", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TFP", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TIP", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TIV", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TMP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TPC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TPT", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_TRT", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each 2 Ref/6 Int */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_RTYPE_REFERENCE, 2, ACPI_RTYPE_INTEGER,
		     6, 0),

	अणुअणु"_TSD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each 5 Int with count */
	PACKAGE_INFO(ACPI_PTYPE2_COUNT, ACPI_RTYPE_INTEGER, 5, 0, 0, 0),

	अणुअणु"_TSN", METHOD_0ARGS,	/* ACPI 6.0 */
	  METHOD_RETURNS(ACPI_RTYPE_REFERENCE)पूर्णपूर्ण,

	अणुअणु"_TSP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TSS", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Pkgs) each 5 Int */
	PACKAGE_INFO(ACPI_PTYPE2, ACPI_RTYPE_INTEGER, 5, 0, 0, 0),

	अणुअणु"_TST", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_TTS", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_NO_RETURN_VALUEपूर्णपूर्ण,

	अणुअणु"_TZD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Variable-length (Refs) */
	PACKAGE_INFO(ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0, 0, 0, 0),

	अणुअणु"_TZM", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_REFERENCE)पूर्णपूर्ण,

	अणुअणु"_TZP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_UID", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING)पूर्णपूर्ण,

	अणुअणु"_UPC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,	/* Fixed-length (4 Int) */
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4, 0, 0, 0),

	अणुअणु"_UPD", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_UPP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	अणुअणु"_VPO", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,

	/* Acpi 1.0 defined _WAK with no वापस value. Later, it was changed to वापस a package */

	अणुअणु"_WAK", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_NONE | ACPI_RTYPE_INTEGER |
			 ACPI_RTYPE_PACKAGE)पूर्णपूर्ण,
	PACKAGE_INFO(ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 2, 0, 0, 0),	/* Fixed-length (2 Int), but is optional */

	/* _WDG/_WED are MS extensions defined by "Windows Instrumentation" */

	अणुअणु"_WDG", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_WED", METHOD_1ARGS(ACPI_TYPE_INTEGER),
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING |
			 ACPI_RTYPE_BUFFER)पूर्णपूर्ण,

	अणुअणु"_WPC", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* ACPI 6.1 */

	अणुअणु"_WPP", METHOD_0ARGS,
	  METHOD_RETURNS(ACPI_RTYPE_INTEGER)पूर्णपूर्ण,	/* ACPI 6.1 */

	PACKAGE_INFO(0, 0, 0, 0, 0, 0)	/* Table terminator */
पूर्ण;
#अन्यथा
बाह्य स्थिर जोड़ acpi_predefined_info acpi_gbl_predefined_methods[];
#पूर्ण_अगर

#अगर (defined ACPI_CREATE_RESOURCE_TABLE && defined ACPI_APPLICATION)
/******************************************************************************
 *
 * Predefined names क्रम use in Resource Descriptors. These names करो not
 * appear in the global Predefined Name table (since these names never
 * appear in actual AML byte code, only in the original ASL)
 *
 * Note: Used by iASL compiler and acpi_help utility only.
 *
 *****************************************************************************/

स्थिर जोड़ acpi_predefined_info acpi_gbl_resource_names[] = अणु
	अणुअणु"_ADR", WIDTH_16 | WIDTH_64, 0पूर्णपूर्ण,
	अणुअणु"_ALN", WIDTH_8 | WIDTH_16 | WIDTH_32, 0पूर्णपूर्ण,
	अणुअणु"_ASI", WIDTH_8, 0पूर्णपूर्ण,
	अणुअणु"_ASZ", WIDTH_8, 0पूर्णपूर्ण,
	अणुअणु"_ATT", WIDTH_64, 0पूर्णपूर्ण,
	अणुअणु"_BAS", WIDTH_16 | WIDTH_32, 0पूर्णपूर्ण,
	अणुअणु"_BM_", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_DBT", WIDTH_16, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_DEC", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_DMA", WIDTH_8, 0पूर्णपूर्ण,
	अणुअणु"_DPL", WIDTH_1, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_DRS", WIDTH_16, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_END", WIDTH_1, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_FLC", WIDTH_2, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_GRA", WIDTH_ADDRESS, 0पूर्णपूर्ण,
	अणुअणु"_HE_", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_INT", WIDTH_16 | WIDTH_32, 0पूर्णपूर्ण,
	अणुअणु"_IOR", WIDTH_2, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_LEN", WIDTH_8 | WIDTH_ADDRESS, 0पूर्णपूर्ण,
	अणुअणु"_LIN", WIDTH_8, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_LL_", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_MAF", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_MAX", WIDTH_ADDRESS, 0पूर्णपूर्ण,
	अणुअणु"_MEM", WIDTH_2, 0पूर्णपूर्ण,
	अणुअणु"_MIF", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_MIN", WIDTH_ADDRESS, 0पूर्णपूर्ण,
	अणुअणु"_MOD", WIDTH_1, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_MTP", WIDTH_2, 0पूर्णपूर्ण,
	अणुअणु"_PAR", WIDTH_8, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_PHA", WIDTH_1, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_PIN", WIDTH_16, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_PPI", WIDTH_8, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_POL", WIDTH_1 | WIDTH_2, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_RBO", WIDTH_8, 0पूर्णपूर्ण,
	अणुअणु"_RBW", WIDTH_8, 0पूर्णपूर्ण,
	अणुअणु"_RNG", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_RT_", WIDTH_8, 0पूर्णपूर्ण,	/* Acpi 3.0 */
	अणुअणु"_RW_", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_RXL", WIDTH_16, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_SHR", WIDTH_2, 0पूर्णपूर्ण,
	अणुअणु"_SIZ", WIDTH_2, 0पूर्णपूर्ण,
	अणुअणु"_SLV", WIDTH_1, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_SPE", WIDTH_32, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_STB", WIDTH_2, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_TRA", WIDTH_ADDRESS, 0पूर्णपूर्ण,
	अणुअणु"_TRS", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_TSF", WIDTH_8, 0पूर्णपूर्ण,	/* Acpi 3.0 */
	अणुअणु"_TTP", WIDTH_1, 0पूर्णपूर्ण,
	अणुअणु"_TXL", WIDTH_16, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	अणुअणु"_TYP", WIDTH_2 | WIDTH_16, 0पूर्णपूर्ण,
	अणुअणु"_VEN", VARIABLE_DATA, 0पूर्णपूर्ण,	/* Acpi 5.0 */
	PACKAGE_INFO(0, 0, 0, 0, 0, 0)	/* Table terminator */
पूर्ण;

स्थिर जोड़ acpi_predefined_info acpi_gbl_scope_names[] = अणु
	अणुअणु"_GPE", 0, 0पूर्णपूर्ण,
	अणुअणु"_PR_", 0, 0पूर्णपूर्ण,
	अणुअणु"_SB_", 0, 0पूर्णपूर्ण,
	अणुअणु"_SI_", 0, 0पूर्णपूर्ण,
	अणुअणु"_TZ_", 0, 0पूर्णपूर्ण,
	PACKAGE_INFO(0, 0, 0, 0, 0, 0)	/* Table terminator */
पूर्ण;
#अन्यथा
बाह्य स्थिर जोड़ acpi_predefined_info acpi_gbl_resource_names[];
#पूर्ण_अगर

#पूर्ण_अगर
