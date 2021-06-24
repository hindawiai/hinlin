<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004 Steven J. Hill
 * Copyright (C) 2001,2002,2003 Broadcom Corporation
 * Copyright (C) 1995-2000 Simon G. Vogl
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_smbus.h>


काष्ठा i2c_algo_sibyte_data अणु
	व्योम *data;		/* निजी data */
	पूर्णांक   bus;		/* which bus */
	व्योम *reg_base;		/* CSR base */
पूर्ण;

/* ----- global defines ----------------------------------------------- */
#घोषणा SMB_CSR(a,r) ((दीर्घ)(a->reg_base + r))


अटल पूर्णांक smbus_xfer(काष्ठा i2c_adapter *i2c_adap, u16 addr,
		      अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		      u8 command, पूर्णांक size, जोड़ i2c_smbus_data * data)
अणु
	काष्ठा i2c_algo_sibyte_data *adap = i2c_adap->algo_data;
	पूर्णांक data_bytes = 0;
	पूर्णांक error;

	जबतक (csr_in32(SMB_CSR(adap, R_SMB_STATUS)) & M_SMB_BUSY)
		;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		csr_out32((V_SMB_ADDR(addr) |
			   (पढ़ो_ग_लिखो == I2C_SMBUS_READ ? M_SMB_QDATA : 0) |
			   V_SMB_TT_QUICKCMD), SMB_CSR(adap, R_SMB_START));
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			csr_out32((V_SMB_ADDR(addr) | V_SMB_TT_RD1BYTE),
				  SMB_CSR(adap, R_SMB_START));
			data_bytes = 1;
		पूर्ण अन्यथा अणु
			csr_out32(V_SMB_CMD(command), SMB_CSR(adap, R_SMB_CMD));
			csr_out32((V_SMB_ADDR(addr) | V_SMB_TT_WR1BYTE),
				  SMB_CSR(adap, R_SMB_START));
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		csr_out32(V_SMB_CMD(command), SMB_CSR(adap, R_SMB_CMD));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			csr_out32((V_SMB_ADDR(addr) | V_SMB_TT_CMD_RD1BYTE),
				  SMB_CSR(adap, R_SMB_START));
			data_bytes = 1;
		पूर्ण अन्यथा अणु
			csr_out32(V_SMB_LB(data->byte),
				  SMB_CSR(adap, R_SMB_DATA));
			csr_out32((V_SMB_ADDR(addr) | V_SMB_TT_WR2BYTE),
				  SMB_CSR(adap, R_SMB_START));
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		csr_out32(V_SMB_CMD(command), SMB_CSR(adap, R_SMB_CMD));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			csr_out32((V_SMB_ADDR(addr) | V_SMB_TT_CMD_RD2BYTE),
				  SMB_CSR(adap, R_SMB_START));
			data_bytes = 2;
		पूर्ण अन्यथा अणु
			csr_out32(V_SMB_LB(data->word & 0xff),
				  SMB_CSR(adap, R_SMB_DATA));
			csr_out32(V_SMB_MB(data->word >> 8),
				  SMB_CSR(adap, R_SMB_DATA));
			csr_out32((V_SMB_ADDR(addr) | V_SMB_TT_WR2BYTE),
				  SMB_CSR(adap, R_SMB_START));
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	जबतक (csr_in32(SMB_CSR(adap, R_SMB_STATUS)) & M_SMB_BUSY)
		;

	error = csr_in32(SMB_CSR(adap, R_SMB_STATUS));
	अगर (error & M_SMB_ERROR) अणु
		/* Clear error bit by writing a 1 */
		csr_out32(M_SMB_ERROR, SMB_CSR(adap, R_SMB_STATUS));
		वापस (error & M_SMB_ERROR_TYPE) ? -EIO : -ENXIO;
	पूर्ण

	अगर (data_bytes == 1)
		data->byte = csr_in32(SMB_CSR(adap, R_SMB_DATA)) & 0xff;
	अगर (data_bytes == 2)
		data->word = csr_in32(SMB_CSR(adap, R_SMB_DATA)) & 0xffff;

	वापस 0;
पूर्ण

अटल u32 bit_func(काष्ठा i2c_adapter *adap)
अणु
	वापस (I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA);
पूर्ण


/* -----exported algorithm data: -------------------------------------	*/

अटल स्थिर काष्ठा i2c_algorithm i2c_sibyte_algo = अणु
	.smbus_xfer	= smbus_xfer,
	.functionality	= bit_func,
पूर्ण;

/*
 * रेजिस्टरing functions to load algorithms at runसमय
 */
अटल पूर्णांक __init i2c_sibyte_add_bus(काष्ठा i2c_adapter *i2c_adap, पूर्णांक speed)
अणु
	काष्ठा i2c_algo_sibyte_data *adap = i2c_adap->algo_data;

	/* Register new adapter to i2c module... */
	i2c_adap->algo = &i2c_sibyte_algo;

	/* Set the requested frequency. */
	csr_out32(speed, SMB_CSR(adap,R_SMB_FREQ));
	csr_out32(0, SMB_CSR(adap,R_SMB_CONTROL));

	वापस i2c_add_numbered_adapter(i2c_adap);
पूर्ण


अटल काष्ठा i2c_algo_sibyte_data sibyte_board_data[2] = अणु
	अणु शून्य, 0, (व्योम *) (CKSEG1+A_SMB_BASE(0)) पूर्ण,
	अणु शून्य, 1, (व्योम *) (CKSEG1+A_SMB_BASE(1)) पूर्ण
पूर्ण;

अटल काष्ठा i2c_adapter sibyte_board_adapter[2] = अणु
	अणु
		.owner		= THIS_MODULE,
		.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
		.algo		= शून्य,
		.algo_data	= &sibyte_board_data[0],
		.nr		= 0,
		.name		= "SiByte SMBus 0",
	पूर्ण,
	अणु
		.owner		= THIS_MODULE,
		.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
		.algo		= शून्य,
		.algo_data	= &sibyte_board_data[1],
		.nr		= 1,
		.name		= "SiByte SMBus 1",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init i2c_sibyte_init(व्योम)
अणु
	pr_info("i2c-sibyte: i2c SMBus adapter module for SiByte board\n");
	अगर (i2c_sibyte_add_bus(&sibyte_board_adapter[0], K_SMB_FREQ_100KHZ) < 0)
		वापस -ENODEV;
	अगर (i2c_sibyte_add_bus(&sibyte_board_adapter[1],
			       K_SMB_FREQ_400KHZ) < 0) अणु
		i2c_del_adapter(&sibyte_board_adapter[0]);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास i2c_sibyte_निकास(व्योम)
अणु
	i2c_del_adapter(&sibyte_board_adapter[0]);
	i2c_del_adapter(&sibyte_board_adapter[1]);
पूर्ण

module_init(i2c_sibyte_init);
module_निकास(i2c_sibyte_निकास);

MODULE_AUTHOR("Kip Walker (Broadcom Corp.)");
MODULE_AUTHOR("Steven J. Hill <sjhill@realitydiluted.com>");
MODULE_DESCRIPTION("SMBus adapter routines for SiByte boards");
MODULE_LICENSE("GPL");
