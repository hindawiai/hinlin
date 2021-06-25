<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utprपूर्णांक - Formatted prपूर्णांकing routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utprint")

#घोषणा ACPI_FORMAT_SIGN            0x01
#घोषणा ACPI_FORMAT_SIGN_PLUS       0x02
#घोषणा ACPI_FORMAT_SIGN_PLUS_SPACE 0x04
#घोषणा ACPI_FORMAT_ZERO            0x08
#घोषणा ACPI_FORMAT_LEFT            0x10
#घोषणा ACPI_FORMAT_UPPER           0x20
#घोषणा ACPI_FORMAT_PREFIX          0x40
/* Local prototypes */
अटल acpi_size
acpi_ut_bound_string_length(स्थिर अक्षर *string, acpi_size count);

अटल अक्षर *acpi_ut_bound_string_output(अक्षर *string, स्थिर अक्षर *end, अक्षर c);

अटल अक्षर *acpi_ut_क्रमmat_number(अक्षर *string,
				   अक्षर *end,
				   u64 number,
				   u8 base, s32 width, s32 precision, u8 type);

अटल अक्षर *acpi_ut_put_number(अक्षर *string, u64 number, u8 base, u8 upper);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_bound_string_length
 *
 * PARAMETERS:  string              - String with boundary
 *              count               - Boundary of the string
 *
 * RETURN:      Length of the string. Less than or equal to Count.
 *
 * DESCRIPTION: Calculate the length of a string with boundary.
 *
 ******************************************************************************/

अटल acpi_size
acpi_ut_bound_string_length(स्थिर अक्षर *string, acpi_size count)
अणु
	u32 length = 0;

	जबतक (*string && count) अणु
		length++;
		string++;
		count--;
	पूर्ण

	वापस (length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_bound_string_output
 *
 * PARAMETERS:  string              - String with boundary
 *              end                 - Boundary of the string
 *              c                   - Character to be output to the string
 *
 * RETURN:      Updated position क्रम next valid अक्षरacter
 *
 * DESCRIPTION: Output a अक्षरacter पूर्णांकo a string with boundary check.
 *
 ******************************************************************************/

अटल अक्षर *acpi_ut_bound_string_output(अक्षर *string, स्थिर अक्षर *end, अक्षर c)
अणु

	अगर (string < end) अणु
		*string = c;
	पूर्ण

	++string;
	वापस (string);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_put_number
 *
 * PARAMETERS:  string              - Buffer to hold reverse-ordered string
 *              number              - Integer to be converted
 *              base                - Base of the पूर्णांकeger
 *              upper               - Whether or not using upper हालd digits
 *
 * RETURN:      Updated position क्रम next valid अक्षरacter
 *
 * DESCRIPTION: Convert an पूर्णांकeger पूर्णांकo a string, note that, the string holds a
 *              reversed ordered number without the trailing zero.
 *
 ******************************************************************************/

अटल अक्षर *acpi_ut_put_number(अक्षर *string, u64 number, u8 base, u8 upper)
अणु
	स्थिर अक्षर *digits;
	u64 digit_index;
	अक्षर *pos;

	pos = string;
	digits = upper ? acpi_gbl_upper_hex_digits : acpi_gbl_lower_hex_digits;

	अगर (number == 0) अणु
		*(pos++) = '0';
	पूर्ण अन्यथा अणु
		जबतक (number) अणु
			(व्योम)acpi_ut_भागide(number, base, &number,
					     &digit_index);
			*(pos++) = digits[digit_index];
		पूर्ण
	पूर्ण

	/* *(Pos++) = '0'; */
	वापस (pos);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_scan_number
 *
 * PARAMETERS:  string              - String buffer
 *              number_ptr          - Where the number is वापसed
 *
 * RETURN:      Updated position क्रम next valid अक्षरacter
 *
 * DESCRIPTION: Scan a string क्रम a decimal पूर्णांकeger.
 *
 ******************************************************************************/

स्थिर अक्षर *acpi_ut_scan_number(स्थिर अक्षर *string, u64 *number_ptr)
अणु
	u64 number = 0;

	जबतक (है_अंक((पूर्णांक)*string)) अणु
		acpi_ut_लघु_multiply(number, 10, &number);
		number += *(string++) - '0';
	पूर्ण

	*number_ptr = number;
	वापस (string);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_prपूर्णांक_number
 *
 * PARAMETERS:  string              - String buffer
 *              number              - The number to be converted
 *
 * RETURN:      Updated position क्रम next valid अक्षरacter
 *
 * DESCRIPTION: Prपूर्णांक a decimal पूर्णांकeger पूर्णांकo a string.
 *
 ******************************************************************************/

स्थिर अक्षर *acpi_ut_prपूर्णांक_number(अक्षर *string, u64 number)
अणु
	अक्षर ascii_string[20];
	स्थिर अक्षर *pos1;
	अक्षर *pos2;

	pos1 = acpi_ut_put_number(ascii_string, number, 10, FALSE);
	pos2 = string;

	जबतक (pos1 != ascii_string) अणु
		*(pos2++) = *(--pos1);
	पूर्ण

	*pos2 = 0;
	वापस (string);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_क्रमmat_number
 *
 * PARAMETERS:  string              - String buffer with boundary
 *              end                 - Boundary of the string
 *              number              - The number to be converted
 *              base                - Base of the पूर्णांकeger
 *              width               - Field width
 *              precision           - Precision of the पूर्णांकeger
 *              type                - Special prपूर्णांकing flags
 *
 * RETURN:      Updated position क्रम next valid अक्षरacter
 *
 * DESCRIPTION: Prपूर्णांक an पूर्णांकeger पूर्णांकo a string with any base and any precision.
 *
 ******************************************************************************/

अटल अक्षर *acpi_ut_क्रमmat_number(अक्षर *string,
				   अक्षर *end,
				   u64 number,
				   u8 base, s32 width, s32 precision, u8 type)
अणु
	अक्षर *pos;
	अक्षर sign;
	अक्षर zero;
	u8 need_prefix;
	u8 upper;
	s32 i;
	अक्षर reversed_string[66];

	/* Parameter validation */

	अगर (base < 2 || base > 16) अणु
		वापस (शून्य);
	पूर्ण

	अगर (type & ACPI_FORMAT_LEFT) अणु
		type &= ~ACPI_FORMAT_ZERO;
	पूर्ण

	need_prefix = ((type & ACPI_FORMAT_PREFIX)
		       && base != 10) ? TRUE : FALSE;
	upper = (type & ACPI_FORMAT_UPPER) ? TRUE : FALSE;
	zero = (type & ACPI_FORMAT_ZERO) ? '0' : ' ';

	/* Calculate size according to sign and prefix */

	sign = '\0';
	अगर (type & ACPI_FORMAT_SIGN) अणु
		अगर ((s64)number < 0) अणु
			sign = '-';
			number = -(s64)number;
			width--;
		पूर्ण अन्यथा अगर (type & ACPI_FORMAT_SIGN_PLUS) अणु
			sign = '+';
			width--;
		पूर्ण अन्यथा अगर (type & ACPI_FORMAT_SIGN_PLUS_SPACE) अणु
			sign = ' ';
			width--;
		पूर्ण
	पूर्ण
	अगर (need_prefix) अणु
		width--;
		अगर (base == 16) अणु
			width--;
		पूर्ण
	पूर्ण

	/* Generate full string in reverse order */

	pos = acpi_ut_put_number(reversed_string, number, base, upper);
	i = (s32)ACPI_PTR_DIFF(pos, reversed_string);

	/* Prपूर्णांकing 100 using %2d gives "100", not "00" */

	अगर (i > precision) अणु
		precision = i;
	पूर्ण

	width -= precision;

	/* Output the string */

	अगर (!(type & (ACPI_FORMAT_ZERO | ACPI_FORMAT_LEFT))) अणु
		जबतक (--width >= 0) अणु
			string = acpi_ut_bound_string_output(string, end, ' ');
		पूर्ण
	पूर्ण
	अगर (sign) अणु
		string = acpi_ut_bound_string_output(string, end, sign);
	पूर्ण
	अगर (need_prefix) अणु
		string = acpi_ut_bound_string_output(string, end, '0');
		अगर (base == 16) अणु
			string =
			    acpi_ut_bound_string_output(string, end,
							upper ? 'X' : 'x');
		पूर्ण
	पूर्ण
	अगर (!(type & ACPI_FORMAT_LEFT)) अणु
		जबतक (--width >= 0) अणु
			string = acpi_ut_bound_string_output(string, end, zero);
		पूर्ण
	पूर्ण

	जबतक (i <= --precision) अणु
		string = acpi_ut_bound_string_output(string, end, '0');
	पूर्ण
	जबतक (--i >= 0) अणु
		string = acpi_ut_bound_string_output(string, end,
						     reversed_string[i]);
	पूर्ण
	जबतक (--width >= 0) अणु
		string = acpi_ut_bound_string_output(string, end, ' ');
	पूर्ण

	वापस (string);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    vsnम_लिखो
 *
 * PARAMETERS:  string              - String with boundary
 *              size                - Boundary of the string
 *              क्रमmat              - Standard म_लिखो क्रमmat
 *              args                - Argument list
 *
 * RETURN:      Number of bytes actually written.
 *
 * DESCRIPTION: Formatted output to a string using argument list poपूर्णांकer.
 *
 ******************************************************************************/

पूर्णांक vsnम_लिखो(अक्षर *string, acpi_size size, स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	u8 base;
	u8 type;
	s32 width;
	s32 precision;
	अक्षर qualअगरier;
	u64 number;
	अक्षर *pos;
	अक्षर *end;
	अक्षर c;
	स्थिर अक्षर *s;
	स्थिर व्योम *p;
	s32 length;
	पूर्णांक i;

	pos = string;

	अगर (size != ACPI_UINT32_MAX) अणु
		end = string + size;
	पूर्ण अन्यथा अणु
		end = ACPI_CAST_PTR(अक्षर, ACPI_UINT32_MAX);
	पूर्ण

	क्रम (; *क्रमmat; ++क्रमmat) अणु
		अगर (*क्रमmat != '%') अणु
			pos = acpi_ut_bound_string_output(pos, end, *क्रमmat);
			जारी;
		पूर्ण

		type = 0;
		base = 10;

		/* Process sign */

		करो अणु
			++क्रमmat;
			अगर (*क्रमmat == '#') अणु
				type |= ACPI_FORMAT_PREFIX;
			पूर्ण अन्यथा अगर (*क्रमmat == '0') अणु
				type |= ACPI_FORMAT_ZERO;
			पूर्ण अन्यथा अगर (*क्रमmat == '+') अणु
				type |= ACPI_FORMAT_SIGN_PLUS;
			पूर्ण अन्यथा अगर (*क्रमmat == ' ') अणु
				type |= ACPI_FORMAT_SIGN_PLUS_SPACE;
			पूर्ण अन्यथा अगर (*क्रमmat == '-') अणु
				type |= ACPI_FORMAT_LEFT;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण

		पूर्ण जबतक (1);

		/* Process width */

		width = -1;
		अगर (है_अंक((पूर्णांक)*क्रमmat)) अणु
			क्रमmat = acpi_ut_scan_number(क्रमmat, &number);
			width = (s32)number;
		पूर्ण अन्यथा अगर (*क्रमmat == '*') अणु
			++क्रमmat;
			width = बहु_तर्क(args, पूर्णांक);
			अगर (width < 0) अणु
				width = -width;
				type |= ACPI_FORMAT_LEFT;
			पूर्ण
		पूर्ण

		/* Process precision */

		precision = -1;
		अगर (*क्रमmat == '.') अणु
			++क्रमmat;
			अगर (है_अंक((पूर्णांक)*क्रमmat)) अणु
				क्रमmat = acpi_ut_scan_number(क्रमmat, &number);
				precision = (s32)number;
			पूर्ण अन्यथा अगर (*क्रमmat == '*') अणु
				++क्रमmat;
				precision = बहु_तर्क(args, पूर्णांक);
			पूर्ण

			अगर (precision < 0) अणु
				precision = 0;
			पूर्ण
		पूर्ण

		/* Process qualअगरier */

		qualअगरier = -1;
		अगर (*क्रमmat == 'h' || *format == 'l' || *format == 'L') अणु
			qualअगरier = *क्रमmat;
			++क्रमmat;

			अगर (qualअगरier == 'l' && *format == 'l') अणु
				qualअगरier = 'L';
				++क्रमmat;
			पूर्ण
		पूर्ण

		चयन (*क्रमmat) अणु
		हाल '%':

			pos = acpi_ut_bound_string_output(pos, end, '%');
			जारी;

		हाल 'c':

			अगर (!(type & ACPI_FORMAT_LEFT)) अणु
				जबतक (--width > 0) अणु
					pos =
					    acpi_ut_bound_string_output(pos,
									end,
									' ');
				पूर्ण
			पूर्ण

			c = (अक्षर)बहु_तर्क(args, पूर्णांक);
			pos = acpi_ut_bound_string_output(pos, end, c);

			जबतक (--width > 0) अणु
				pos =
				    acpi_ut_bound_string_output(pos, end, ' ');
			पूर्ण
			जारी;

		हाल 's':

			s = बहु_तर्क(args, अक्षर *);
			अगर (!s) अणु
				s = "<NULL>";
			पूर्ण
			length = (s32)acpi_ut_bound_string_length(s, precision);
			अगर (!(type & ACPI_FORMAT_LEFT)) अणु
				जबतक (length < width--) अणु
					pos =
					    acpi_ut_bound_string_output(pos,
									end,
									' ');
				पूर्ण
			पूर्ण

			क्रम (i = 0; i < length; ++i) अणु
				pos = acpi_ut_bound_string_output(pos, end, *s);
				++s;
			पूर्ण

			जबतक (length < width--) अणु
				pos =
				    acpi_ut_bound_string_output(pos, end, ' ');
			पूर्ण
			जारी;

		हाल 'o':

			base = 8;
			अवरोध;

		हाल 'X':

			type |= ACPI_FORMAT_UPPER;
			/* FALLTHROUGH */

		हाल 'x':

			base = 16;
			अवरोध;

		हाल 'd':
		हाल 'i':

			type |= ACPI_FORMAT_SIGN;

		हाल 'u':

			अवरोध;

		हाल 'p':

			अगर (width == -1) अणु
				width = 2 * माप(व्योम *);
				type |= ACPI_FORMAT_ZERO;
			पूर्ण

			p = बहु_तर्क(args, व्योम *);
			pos =
			    acpi_ut_क्रमmat_number(pos, end, ACPI_TO_INTEGER(p),
						  16, width, precision, type);
			जारी;

		शेष:

			pos = acpi_ut_bound_string_output(pos, end, '%');
			अगर (*क्रमmat) अणु
				pos =
				    acpi_ut_bound_string_output(pos, end,
								*क्रमmat);
			पूर्ण अन्यथा अणु
				--क्रमmat;
			पूर्ण
			जारी;
		पूर्ण

		अगर (qualअगरier == 'L') अणु
			number = बहु_तर्क(args, u64);
			अगर (type & ACPI_FORMAT_SIGN) अणु
				number = (s64)number;
			पूर्ण
		पूर्ण अन्यथा अगर (qualअगरier == 'l') अणु
			number = बहु_तर्क(args, अचिन्हित दीर्घ);
			अगर (type & ACPI_FORMAT_SIGN) अणु
				number = (s32)number;
			पूर्ण
		पूर्ण अन्यथा अगर (qualअगरier == 'h') अणु
			number = (u16)बहु_तर्क(args, पूर्णांक);
			अगर (type & ACPI_FORMAT_SIGN) अणु
				number = (s16)number;
			पूर्ण
		पूर्ण अन्यथा अणु
			number = बहु_तर्क(args, अचिन्हित पूर्णांक);
			अगर (type & ACPI_FORMAT_SIGN) अणु
				number = (चिन्हित पूर्णांक)number;
			पूर्ण
		पूर्ण

		pos = acpi_ut_क्रमmat_number(pos, end, number, base,
					    width, precision, type);
	पूर्ण

	अगर (size > 0) अणु
		अगर (pos < end) अणु
			*pos = '\0';
		पूर्ण अन्यथा अणु
			end[-1] = '\0';
		पूर्ण
	पूर्ण

	वापस ((पूर्णांक)ACPI_PTR_DIFF(pos, string));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    snम_लिखो
 *
 * PARAMETERS:  string              - String with boundary
 *              size                - Boundary of the string
 *              Format, ...         - Standard म_लिखो क्रमmat
 *
 * RETURN:      Number of bytes actually written.
 *
 * DESCRIPTION: Formatted output to a string.
 *
 ******************************************************************************/

पूर्णांक snम_लिखो(अक्षर *string, acpi_size size, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	पूर्णांक length;

	बहु_शुरू(args, क्रमmat);
	length = vsnम_लिखो(string, size, क्रमmat, args);
	बहु_पूर्ण(args);

	वापस (length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    प्र_लिखो
 *
 * PARAMETERS:  string              - String with boundary
 *              Format, ...         - Standard म_लिखो क्रमmat
 *
 * RETURN:      Number of bytes actually written.
 *
 * DESCRIPTION: Formatted output to a string.
 *
 ******************************************************************************/

पूर्णांक प्र_लिखो(अक्षर *string, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	पूर्णांक length;

	बहु_शुरू(args, क्रमmat);
	length = vsnम_लिखो(string, ACPI_UINT32_MAX, क्रमmat, args);
	बहु_पूर्ण(args);

	वापस (length);
पूर्ण

#अगर_घोषित ACPI_APPLICATION
/*******************************************************************************
 *
 * FUNCTION:    भ_लिखो
 *
 * PARAMETERS:  क्रमmat              - Standard म_लिखो क्रमmat
 *              args                - Argument list
 *
 * RETURN:      Number of bytes actually written.
 *
 * DESCRIPTION: Formatted output to मानक_निकास using argument list poपूर्णांकer.
 *
 ******************************************************************************/

पूर्णांक भ_लिखो(स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	acpi_cpu_flags flags;
	पूर्णांक length;

	flags = acpi_os_acquire_lock(acpi_gbl_prपूर्णांक_lock);
	length = vsnम_लिखो(acpi_gbl_prपूर्णांक_buffer,
			   माप(acpi_gbl_prपूर्णांक_buffer), क्रमmat, args);

	(व्योम)ख_डालो(acpi_gbl_prपूर्णांक_buffer, length, 1, ACPI_खाता_OUT);
	acpi_os_release_lock(acpi_gbl_prपूर्णांक_lock, flags);

	वापस (length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    म_लिखो
 *
 * PARAMETERS:  Format, ...         - Standard म_लिखो क्रमmat
 *
 * RETURN:      Number of bytes actually written.
 *
 * DESCRIPTION: Formatted output to मानक_निकास.
 *
 ******************************************************************************/

पूर्णांक म_लिखो(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	पूर्णांक length;

	बहु_शुरू(args, क्रमmat);
	length = भ_लिखो(क्रमmat, args);
	बहु_पूर्ण(args);

	वापस (length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    भख_लिखो
 *
 * PARAMETERS:  file                - File descriptor
 *              क्रमmat              - Standard म_लिखो क्रमmat
 *              args                - Argument list
 *
 * RETURN:      Number of bytes actually written.
 *
 * DESCRIPTION: Formatted output to a file using argument list poपूर्णांकer.
 *
 ******************************************************************************/

पूर्णांक भख_लिखो(खाता * file, स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	acpi_cpu_flags flags;
	पूर्णांक length;

	flags = acpi_os_acquire_lock(acpi_gbl_prपूर्णांक_lock);
	length = vsnम_लिखो(acpi_gbl_prपूर्णांक_buffer,
			   माप(acpi_gbl_prपूर्णांक_buffer), क्रमmat, args);

	(व्योम)ख_डालो(acpi_gbl_prपूर्णांक_buffer, length, 1, file);
	acpi_os_release_lock(acpi_gbl_prपूर्णांक_lock, flags);

	वापस (length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    ख_लिखो
 *
 * PARAMETERS:  file                - File descriptor
 *              Format, ...         - Standard म_लिखो क्रमmat
 *
 * RETURN:      Number of bytes actually written.
 *
 * DESCRIPTION: Formatted output to a file.
 *
 ******************************************************************************/

पूर्णांक ख_लिखो(खाता * file, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	पूर्णांक length;

	बहु_शुरू(args, क्रमmat);
	length = भख_लिखो(file, क्रमmat, args);
	बहु_पूर्ण(args);

	वापस (length);
पूर्ण
#पूर्ण_अगर
