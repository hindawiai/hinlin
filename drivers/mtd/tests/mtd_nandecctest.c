<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>

#समावेश "mtd_test.h"

/*
 * Test the implementation क्रम software ECC
 *
 * No actual MTD device is needed, So we करोn't need to warry about losing
 * important data by human error.
 *
 * This covers possible patterns of corruption which can be reliably corrected
 * or detected.
 */

#अगर IS_ENABLED(CONFIG_MTD_RAW_न_अंकD)

काष्ठा nand_ecc_test अणु
	स्थिर अक्षर *name;
	व्योम (*prepare)(व्योम *, व्योम *, व्योम *, व्योम *, स्थिर माप_प्रकार);
	पूर्णांक (*verअगरy)(व्योम *, व्योम *, व्योम *, स्थिर माप_प्रकार);
पूर्ण;

/*
 * The reason क्रम this __change_bit_le() instead of __change_bit() is to inject
 * bit error properly within the region which is not a multiple of
 * माप(अचिन्हित दीर्घ) on big-endian प्रणालीs
 */
#अगर_घोषित __LITTLE_ENDIAN
#घोषणा __change_bit_le(nr, addr) __change_bit(nr, addr)
#या_अगर defined(__BIG_ENDIAN)
#घोषणा __change_bit_le(nr, addr) \
		__change_bit((nr) ^ ((BITS_PER_LONG - 1) & ~0x7), addr)
#अन्यथा
#त्रुटि "Unknown byte order"
#पूर्ण_अगर

अटल व्योम single_bit_error_data(व्योम *error_data, व्योम *correct_data,
				माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक offset = pअक्रमom_u32() % (size * BITS_PER_BYTE);

	स_नकल(error_data, correct_data, size);
	__change_bit_le(offset, error_data);
पूर्ण

अटल व्योम द्विगुन_bit_error_data(व्योम *error_data, व्योम *correct_data,
				माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक offset[2];

	offset[0] = pअक्रमom_u32() % (size * BITS_PER_BYTE);
	करो अणु
		offset[1] = pअक्रमom_u32() % (size * BITS_PER_BYTE);
	पूर्ण जबतक (offset[0] == offset[1]);

	स_नकल(error_data, correct_data, size);

	__change_bit_le(offset[0], error_data);
	__change_bit_le(offset[1], error_data);
पूर्ण

अटल अचिन्हित पूर्णांक अक्रमom_ecc_bit(माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक offset = pअक्रमom_u32() % (3 * BITS_PER_BYTE);

	अगर (size == 256) अणु
		/*
		 * Don't inject a bit error पूर्णांकo the insignअगरicant bits (16th
		 * and 17th bit) in ECC code क्रम 256 byte data block
		 */
		जबतक (offset == 16 || offset == 17)
			offset = pअक्रमom_u32() % (3 * BITS_PER_BYTE);
	पूर्ण

	वापस offset;
पूर्ण

अटल व्योम single_bit_error_ecc(व्योम *error_ecc, व्योम *correct_ecc,
				माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक offset = अक्रमom_ecc_bit(size);

	स_नकल(error_ecc, correct_ecc, 3);
	__change_bit_le(offset, error_ecc);
पूर्ण

अटल व्योम द्विगुन_bit_error_ecc(व्योम *error_ecc, व्योम *correct_ecc,
				माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक offset[2];

	offset[0] = अक्रमom_ecc_bit(size);
	करो अणु
		offset[1] = अक्रमom_ecc_bit(size);
	पूर्ण जबतक (offset[0] == offset[1]);

	स_नकल(error_ecc, correct_ecc, 3);
	__change_bit_le(offset[0], error_ecc);
	__change_bit_le(offset[1], error_ecc);
पूर्ण

अटल व्योम no_bit_error(व्योम *error_data, व्योम *error_ecc,
		व्योम *correct_data, व्योम *correct_ecc, स्थिर माप_प्रकार size)
अणु
	स_नकल(error_data, correct_data, size);
	स_नकल(error_ecc, correct_ecc, 3);
पूर्ण

अटल पूर्णांक no_bit_error_verअगरy(व्योम *error_data, व्योम *error_ecc,
				व्योम *correct_data, स्थिर माप_प्रकार size)
अणु
	bool sm_order = IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING_SMC);
	अचिन्हित अक्षर calc_ecc[3];
	पूर्णांक ret;

	ecc_sw_hamming_calculate(error_data, size, calc_ecc, sm_order);
	ret = ecc_sw_hamming_correct(error_data, error_ecc, calc_ecc, size,
				     sm_order);
	अगर (ret == 0 && !स_भेद(correct_data, error_data, size))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल व्योम single_bit_error_in_data(व्योम *error_data, व्योम *error_ecc,
		व्योम *correct_data, व्योम *correct_ecc, स्थिर माप_प्रकार size)
अणु
	single_bit_error_data(error_data, correct_data, size);
	स_नकल(error_ecc, correct_ecc, 3);
पूर्ण

अटल व्योम single_bit_error_in_ecc(व्योम *error_data, व्योम *error_ecc,
		व्योम *correct_data, व्योम *correct_ecc, स्थिर माप_प्रकार size)
अणु
	स_नकल(error_data, correct_data, size);
	single_bit_error_ecc(error_ecc, correct_ecc, size);
पूर्ण

अटल पूर्णांक single_bit_error_correct(व्योम *error_data, व्योम *error_ecc,
				व्योम *correct_data, स्थिर माप_प्रकार size)
अणु
	bool sm_order = IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING_SMC);
	अचिन्हित अक्षर calc_ecc[3];
	पूर्णांक ret;

	ecc_sw_hamming_calculate(error_data, size, calc_ecc, sm_order);
	ret = ecc_sw_hamming_correct(error_data, error_ecc, calc_ecc, size,
				     sm_order);
	अगर (ret == 1 && !स_भेद(correct_data, error_data, size))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल व्योम द्विगुन_bit_error_in_data(व्योम *error_data, व्योम *error_ecc,
		व्योम *correct_data, व्योम *correct_ecc, स्थिर माप_प्रकार size)
अणु
	द्विगुन_bit_error_data(error_data, correct_data, size);
	स_नकल(error_ecc, correct_ecc, 3);
पूर्ण

अटल व्योम single_bit_error_in_data_and_ecc(व्योम *error_data, व्योम *error_ecc,
		व्योम *correct_data, व्योम *correct_ecc, स्थिर माप_प्रकार size)
अणु
	single_bit_error_data(error_data, correct_data, size);
	single_bit_error_ecc(error_ecc, correct_ecc, size);
पूर्ण

अटल व्योम द्विगुन_bit_error_in_ecc(व्योम *error_data, व्योम *error_ecc,
		व्योम *correct_data, व्योम *correct_ecc, स्थिर माप_प्रकार size)
अणु
	स_नकल(error_data, correct_data, size);
	द्विगुन_bit_error_ecc(error_ecc, correct_ecc, size);
पूर्ण

अटल पूर्णांक द्विगुन_bit_error_detect(व्योम *error_data, व्योम *error_ecc,
				व्योम *correct_data, स्थिर माप_प्रकार size)
अणु
	bool sm_order = IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING_SMC);
	अचिन्हित अक्षर calc_ecc[3];
	पूर्णांक ret;

	ecc_sw_hamming_calculate(error_data, size, calc_ecc, sm_order);
	ret = ecc_sw_hamming_correct(error_data, error_ecc, calc_ecc, size,
				     sm_order);

	वापस (ret == -EBADMSG) ? 0 : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nand_ecc_test nand_ecc_test[] = अणु
	अणु
		.name = "no-bit-error",
		.prepare = no_bit_error,
		.verअगरy = no_bit_error_verअगरy,
	पूर्ण,
	अणु
		.name = "single-bit-error-in-data-correct",
		.prepare = single_bit_error_in_data,
		.verअगरy = single_bit_error_correct,
	पूर्ण,
	अणु
		.name = "single-bit-error-in-ecc-correct",
		.prepare = single_bit_error_in_ecc,
		.verअगरy = single_bit_error_correct,
	पूर्ण,
	अणु
		.name = "double-bit-error-in-data-detect",
		.prepare = द्विगुन_bit_error_in_data,
		.verअगरy = द्विगुन_bit_error_detect,
	पूर्ण,
	अणु
		.name = "single-bit-error-in-data-and-ecc-detect",
		.prepare = single_bit_error_in_data_and_ecc,
		.verअगरy = द्विगुन_bit_error_detect,
	पूर्ण,
	अणु
		.name = "double-bit-error-in-ecc-detect",
		.prepare = द्विगुन_bit_error_in_ecc,
		.verअगरy = द्विगुन_bit_error_detect,
	पूर्ण,
पूर्ण;

अटल व्योम dump_data_ecc(व्योम *error_data, व्योम *error_ecc, व्योम *correct_data,
			व्योम *correct_ecc, स्थिर माप_प्रकार size)
अणु
	pr_info("hexdump of error data:\n");
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 4,
			error_data, size, false);
	prपूर्णांक_hex_dump(KERN_INFO, "hexdump of error ecc: ",
			DUMP_PREFIX_NONE, 16, 1, error_ecc, 3, false);

	pr_info("hexdump of correct data:\n");
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 4,
			correct_data, size, false);
	prपूर्णांक_hex_dump(KERN_INFO, "hexdump of correct ecc: ",
			DUMP_PREFIX_NONE, 16, 1, correct_ecc, 3, false);
पूर्ण

अटल पूर्णांक nand_ecc_test_run(स्थिर माप_प्रकार size)
अणु
	bool sm_order = IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING_SMC);
	पूर्णांक i;
	पूर्णांक err = 0;
	व्योम *error_data;
	व्योम *error_ecc;
	व्योम *correct_data;
	व्योम *correct_ecc;

	error_data = kदो_स्मृति(size, GFP_KERNEL);
	error_ecc = kदो_स्मृति(3, GFP_KERNEL);
	correct_data = kदो_स्मृति(size, GFP_KERNEL);
	correct_ecc = kदो_स्मृति(3, GFP_KERNEL);

	अगर (!error_data || !error_ecc || !correct_data || !correct_ecc) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	pअक्रमom_bytes(correct_data, size);
	ecc_sw_hamming_calculate(correct_data, size, correct_ecc, sm_order);
	क्रम (i = 0; i < ARRAY_SIZE(nand_ecc_test); i++) अणु
		nand_ecc_test[i].prepare(error_data, error_ecc,
				correct_data, correct_ecc, size);
		err = nand_ecc_test[i].verअगरy(error_data, error_ecc,
						correct_data, size);

		अगर (err) अणु
			pr_err("not ok - %s-%zd\n",
				nand_ecc_test[i].name, size);
			dump_data_ecc(error_data, error_ecc,
				correct_data, correct_ecc, size);
			अवरोध;
		पूर्ण
		pr_info("ok - %s-%zd\n",
			nand_ecc_test[i].name, size);

		err = mtdtest_relax();
		अगर (err)
			अवरोध;
	पूर्ण
error:
	kमुक्त(error_data);
	kमुक्त(error_ecc);
	kमुक्त(correct_data);
	kमुक्त(correct_ecc);

	वापस err;
पूर्ण

#अन्यथा

अटल पूर्णांक nand_ecc_test_run(स्थिर माप_प्रकार size)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init ecc_test_init(व्योम)
अणु
	पूर्णांक err;

	err = nand_ecc_test_run(256);
	अगर (err)
		वापस err;

	वापस nand_ecc_test_run(512);
पूर्ण

अटल व्योम __निकास ecc_test_निकास(व्योम)
अणु
पूर्ण

module_init(ecc_test_init);
module_निकास(ecc_test_निकास);

MODULE_DESCRIPTION("NAND ECC function test module");
MODULE_AUTHOR("Akinobu Mita");
MODULE_LICENSE("GPL");
