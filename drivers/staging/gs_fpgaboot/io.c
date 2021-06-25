<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>

#समावेश "io.h"

अटल अंतरभूत व्योम byte0_out(अचिन्हित अक्षर data);
अटल अंतरभूत व्योम byte1_out(अचिन्हित अक्षर data);
अटल अंतरभूत व्योम xl_cclk_b(पूर्णांक32_t i);

/* Assert and Deनिश्चित CCLK */
व्योम xl_shअगरt_cclk(पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		xl_cclk_b(1);
		xl_cclk_b(0);
	पूर्ण
पूर्ण

पूर्णांक xl_supported_prog_bus_width(क्रमागत wbus bus_bytes)
अणु
	चयन (bus_bytes) अणु
	हाल bus_1byte:
		अवरोध;
	हाल bus_2byte:
		अवरोध;
	शेष:
		pr_err("unsupported program bus width %d\n", bus_bytes);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* Serialize byte and घड़ी each bit on target's DIN and CCLK pins */
व्योम xl_shअगरt_bytes_out(क्रमागत wbus bus_byte, अचिन्हित अक्षर *pdata)
अणु
	/*
	 * supports 1 and 2 bytes programming mode
	 */
	अगर (likely(bus_byte == bus_2byte))
		byte0_out(pdata[0]);

	byte1_out(pdata[1]);
	xl_shअगरt_cclk(1);
पूर्ण

/*
 * generic bit swap क्रम xilinx SYSTEMMAP FPGA programming
 */
व्योम xl_program_b(पूर्णांक32_t i)
अणु
पूर्ण

व्योम xl_rdwr_b(पूर्णांक32_t i)
अणु
पूर्ण

व्योम xl_csi_b(पूर्णांक32_t i)
अणु
पूर्ण

पूर्णांक xl_get_init_b(व्योम)
अणु
	वापस -1;
पूर्ण

पूर्णांक xl_get_करोne_b(व्योम)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम byte0_out(अचिन्हित अक्षर data)
अणु
पूर्ण

अटल अंतरभूत व्योम byte1_out(अचिन्हित अक्षर data)
अणु
पूर्ण

अटल अंतरभूत व्योम xl_cclk_b(पूर्णांक32_t i)
अणु
पूर्ण

/*
 * configurable per device type क्रम dअगरferent I/O config
 */
पूर्णांक xl_init_io(व्योम)
अणु
	वापस -1;
पूर्ण
