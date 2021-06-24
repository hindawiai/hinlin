<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2016
 */
#समावेश <linux/kernel.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/sclp.h>
#समावेश "boot.h"

/*
 * The code within this file will be called very early. It may _not_
 * access anything within the bss section, since that is not cleared
 * yet and may contain data (e.g. initrd) that must be saved by other
 * code.
 * For temporary objects the stack (16k) should be used.
 */

अटल अचिन्हित दीर्घ als[] = अणु FACILITIES_ALS पूर्ण;

अटल व्योम u16_to_hex(अक्षर *str, u16 val)
अणु
	पूर्णांक i, num;

	क्रम (i = 1; i <= 4; i++) अणु
		num = (val >> (16 - 4 * i)) & 0xf;
		अगर (num >= 10)
			num += 7;
		*str++ = '0' + num;
	पूर्ण
	*str = '\0';
पूर्ण

अटल व्योम prपूर्णांक_machine_type(व्योम)
अणु
	अटल अक्षर mach_str[80] = "Detected machine-type number: ";
	अक्षर type_str[5];
	काष्ठा cpuid id;

	get_cpu_id(&id);
	u16_to_hex(type_str, id.machine);
	म_जोड़ो(mach_str, type_str);
	म_जोड़ो(mach_str, "\n");
	sclp_early_prपूर्णांकk(mach_str);
पूर्ण

अटल व्योम u16_to_decimal(अक्षर *str, u16 val)
अणु
	पूर्णांक भाग = 1;

	जबतक (भाग * 10 <= val)
		भाग *= 10;
	जबतक (भाग) अणु
		*str++ = '0' + val / भाग;
		val %= भाग;
		भाग /= 10;
	पूर्ण
	*str = '\0';
पूर्ण

व्योम prपूर्णांक_missing_facilities(व्योम)
अणु
	अटल अक्षर als_str[80] = "Missing facilities: ";
	अचिन्हित दीर्घ val;
	अक्षर val_str[6];
	पूर्णांक i, j, first;

	first = 1;
	क्रम (i = 0; i < ARRAY_SIZE(als); i++) अणु
		val = ~S390_lowcore.stfle_fac_list[i] & als[i];
		क्रम (j = 0; j < BITS_PER_LONG; j++) अणु
			अगर (!(val & (1UL << (BITS_PER_LONG - 1 - j))))
				जारी;
			अगर (!first)
				म_जोड़ो(als_str, ",");
			/*
			 * Make sure we stay within one line. Consider that
			 * each facility bit adds up to five अक्षरacters and
			 * z/VM adds a four अक्षरacter prefix.
			 */
			अगर (म_माप(als_str) > 70) अणु
				म_जोड़ो(als_str, "\n");
				sclp_early_prपूर्णांकk(als_str);
				*als_str = '\0';
			पूर्ण
			u16_to_decimal(val_str, i * BITS_PER_LONG + j);
			म_जोड़ो(als_str, val_str);
			first = 0;
		पूर्ण
	पूर्ण
	म_जोड़ो(als_str, "\n");
	sclp_early_prपूर्णांकk(als_str);
पूर्ण

अटल व्योम facility_mismatch(व्योम)
अणु
	sclp_early_prपूर्णांकk("The Linux kernel requires more recent processor hardware\n");
	prपूर्णांक_machine_type();
	prपूर्णांक_missing_facilities();
	sclp_early_prपूर्णांकk("See Principles of Operations for facility bits\n");
	disabled_रुको();
पूर्ण

व्योम verअगरy_facilities(व्योम)
अणु
	पूर्णांक i;

	__stfle(S390_lowcore.stfle_fac_list, ARRAY_SIZE(S390_lowcore.stfle_fac_list));
	क्रम (i = 0; i < ARRAY_SIZE(als); i++) अणु
		अगर ((S390_lowcore.stfle_fac_list[i] & als[i]) != als[i])
			facility_mismatch();
	पूर्ण
पूर्ण
