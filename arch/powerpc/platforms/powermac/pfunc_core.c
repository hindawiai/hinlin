<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * FIXME: Properly make this race मुक्त with refcounting etc...
 *
 * FIXME: LOCKING !!!
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pmac_pfunc.h>

/* Debug */
#घोषणा LOG_PARSE(fmt...)
#घोषणा LOG_ERROR(fmt...)	prपूर्णांकk(fmt)
#घोषणा LOG_BLOB(t,b,c)

#अघोषित DEBUG
#अगर_घोषित DEBUG
#घोषणा DBG(fmt...)		prपूर्णांकk(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

/* Command numbers */
#घोषणा PMF_CMD_LIST			0
#घोषणा PMF_CMD_WRITE_GPIO		1
#घोषणा PMF_CMD_READ_GPIO		2
#घोषणा PMF_CMD_WRITE_REG32		3
#घोषणा PMF_CMD_READ_REG32		4
#घोषणा PMF_CMD_WRITE_REG16		5
#घोषणा PMF_CMD_READ_REG16		6
#घोषणा PMF_CMD_WRITE_REG8		7
#घोषणा PMF_CMD_READ_REG8		8
#घोषणा PMF_CMD_DELAY			9
#घोषणा PMF_CMD_WAIT_REG32		10
#घोषणा PMF_CMD_WAIT_REG16		11
#घोषणा PMF_CMD_WAIT_REG8		12
#घोषणा PMF_CMD_READ_I2C		13
#घोषणा PMF_CMD_WRITE_I2C		14
#घोषणा PMF_CMD_RMW_I2C			15
#घोषणा PMF_CMD_GEN_I2C			16
#घोषणा PMF_CMD_SHIFT_BYTES_RIGHT	17
#घोषणा PMF_CMD_SHIFT_BYTES_LEFT	18
#घोषणा PMF_CMD_READ_CFG		19
#घोषणा PMF_CMD_WRITE_CFG		20
#घोषणा PMF_CMD_RMW_CFG			21
#घोषणा PMF_CMD_READ_I2C_SUBADDR	22
#घोषणा PMF_CMD_WRITE_I2C_SUBADDR	23
#घोषणा PMF_CMD_SET_I2C_MODE		24
#घोषणा PMF_CMD_RMW_I2C_SUBADDR		25
#घोषणा PMF_CMD_READ_REG32_MASK_SHR_XOR	26
#घोषणा PMF_CMD_READ_REG16_MASK_SHR_XOR	27
#घोषणा PMF_CMD_READ_REG8_MASK_SHR_XOR	28
#घोषणा PMF_CMD_WRITE_REG32_SHL_MASK	29
#घोषणा PMF_CMD_WRITE_REG16_SHL_MASK	30
#घोषणा PMF_CMD_WRITE_REG8_SHL_MASK	31
#घोषणा PMF_CMD_MASK_AND_COMPARE	32
#घोषणा PMF_CMD_COUNT			33

/* This काष्ठाure holds the state of the parser जबतक walking through
 * a function definition
 */
काष्ठा pmf_cmd अणु
	स्थिर व्योम		*cmdptr;
	स्थिर व्योम		*cmdend;
	काष्ठा pmf_function	*func;
	व्योम			*instdata;
	काष्ठा pmf_args		*args;
	पूर्णांक			error;
पूर्ण;

#अगर 0
/* Debug output */
अटल व्योम prपूर्णांक_blob(स्थिर अक्षर *title, स्थिर व्योम *blob, पूर्णांक bytes)
अणु
	prपूर्णांकk("%s", title);
	जबतक(bytes--) अणु
		prपूर्णांकk("%02x ", *((u8 *)blob));
		blob += 1;
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण
#पूर्ण_अगर

/*
 * Parser helpers
 */

अटल u32 pmf_next32(काष्ठा pmf_cmd *cmd)
अणु
	u32 value;
	अगर ((cmd->cmdend - cmd->cmdptr) < 4) अणु
		cmd->error = 1;
		वापस 0;
	पूर्ण
	value = *((u32 *)cmd->cmdptr);
	cmd->cmdptr += 4;
	वापस value;
पूर्ण

अटल स्थिर व्योम* pmf_next_blob(काष्ठा pmf_cmd *cmd, पूर्णांक count)
अणु
	स्थिर व्योम *value;
	अगर ((cmd->cmdend - cmd->cmdptr) < count) अणु
		cmd->error = 1;
		वापस शून्य;
	पूर्ण
	value = cmd->cmdptr;
	cmd->cmdptr += count;
	वापस value;
पूर्ण

/*
 * Inभागidual command parsers
 */

#घोषणा PMF_PARSE_CALL(name, cmd, handlers, p...) \
	करो अणु \
		अगर (cmd->error) \
			वापस -ENXIO; \
		अगर (handlers == शून्य) \
			वापस 0; \
		अगर (handlers->name)				      \
			वापस handlers->name(cmd->func, cmd->instdata, \
					      cmd->args, p);	      \
		वापस -1; \
	पूर्ण जबतक(0) \


अटल पूर्णांक pmf_parser_ग_लिखो_gpio(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u8 value = (u8)pmf_next32(cmd);
	u8 mask = (u8)pmf_next32(cmd);

	LOG_PARSE("pmf: write_gpio(value: %02x, mask: %02x)\n", value, mask);

	PMF_PARSE_CALL(ग_लिखो_gpio, cmd, h, value, mask);
पूर्ण

अटल पूर्णांक pmf_parser_पढ़ो_gpio(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u8 mask = (u8)pmf_next32(cmd);
	पूर्णांक rshअगरt = (पूर्णांक)pmf_next32(cmd);
	u8 xor = (u8)pmf_next32(cmd);

	LOG_PARSE("pmf: read_gpio(mask: %02x, rshift: %d, xor: %02x)\n",
		  mask, rshअगरt, xor);

	PMF_PARSE_CALL(पढ़ो_gpio, cmd, h, mask, rshअगरt, xor);
पूर्ण

अटल पूर्णांक pmf_parser_ग_लिखो_reg32(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 value = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	LOG_PARSE("pmf: write_reg32(offset: %08x, value: %08x, mask: %08x)\n",
		  offset, value, mask);

	PMF_PARSE_CALL(ग_लिखो_reg32, cmd, h, offset, value, mask);
पूर्ण

अटल पूर्णांक pmf_parser_पढ़ो_reg32(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);

	LOG_PARSE("pmf: read_reg32(offset: %08x)\n", offset);

	PMF_PARSE_CALL(पढ़ो_reg32, cmd, h, offset);
पूर्ण


अटल पूर्णांक pmf_parser_ग_लिखो_reg16(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u16 value = (u16)pmf_next32(cmd);
	u16 mask = (u16)pmf_next32(cmd);

	LOG_PARSE("pmf: write_reg16(offset: %08x, value: %04x, mask: %04x)\n",
		  offset, value, mask);

	PMF_PARSE_CALL(ग_लिखो_reg16, cmd, h, offset, value, mask);
पूर्ण

अटल पूर्णांक pmf_parser_पढ़ो_reg16(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);

	LOG_PARSE("pmf: read_reg16(offset: %08x)\n", offset);

	PMF_PARSE_CALL(पढ़ो_reg16, cmd, h, offset);
पूर्ण


अटल पूर्णांक pmf_parser_ग_लिखो_reg8(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u8 value = (u16)pmf_next32(cmd);
	u8 mask = (u16)pmf_next32(cmd);

	LOG_PARSE("pmf: write_reg8(offset: %08x, value: %02x, mask: %02x)\n",
		  offset, value, mask);

	PMF_PARSE_CALL(ग_लिखो_reg8, cmd, h, offset, value, mask);
पूर्ण

अटल पूर्णांक pmf_parser_पढ़ो_reg8(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);

	LOG_PARSE("pmf: read_reg8(offset: %08x)\n", offset);

	PMF_PARSE_CALL(पढ़ो_reg8, cmd, h, offset);
पूर्ण

अटल पूर्णांक pmf_parser_delay(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 duration = pmf_next32(cmd);

	LOG_PARSE("pmf: delay(duration: %d us)\n", duration);

	PMF_PARSE_CALL(delay, cmd, h, duration);
पूर्ण

अटल पूर्णांक pmf_parser_रुको_reg32(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 value = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	LOG_PARSE("pmf: wait_reg32(offset: %08x, comp_value: %08x,mask: %08x)\n",
		  offset, value, mask);

	PMF_PARSE_CALL(रुको_reg32, cmd, h, offset, value, mask);
पूर्ण

अटल पूर्णांक pmf_parser_रुको_reg16(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u16 value = (u16)pmf_next32(cmd);
	u16 mask = (u16)pmf_next32(cmd);

	LOG_PARSE("pmf: wait_reg16(offset: %08x, comp_value: %04x,mask: %04x)\n",
		  offset, value, mask);

	PMF_PARSE_CALL(रुको_reg16, cmd, h, offset, value, mask);
पूर्ण

अटल पूर्णांक pmf_parser_रुको_reg8(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u8 value = (u8)pmf_next32(cmd);
	u8 mask = (u8)pmf_next32(cmd);

	LOG_PARSE("pmf: wait_reg8(offset: %08x, comp_value: %02x,mask: %02x)\n",
		  offset, value, mask);

	PMF_PARSE_CALL(रुको_reg8, cmd, h, offset, value, mask);
पूर्ण

अटल पूर्णांक pmf_parser_पढ़ो_i2c(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 bytes = pmf_next32(cmd);

	LOG_PARSE("pmf: read_i2c(bytes: %ud)\n", bytes);

	PMF_PARSE_CALL(पढ़ो_i2c, cmd, h, bytes);
पूर्ण

अटल पूर्णांक pmf_parser_ग_लिखो_i2c(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 bytes = pmf_next32(cmd);
	स्थिर व्योम *blob = pmf_next_blob(cmd, bytes);

	LOG_PARSE("pmf: write_i2c(bytes: %ud) ...\n", bytes);
	LOG_BLOB("pmf:   data: \n", blob, bytes);

	PMF_PARSE_CALL(ग_लिखो_i2c, cmd, h, bytes, blob);
पूर्ण


अटल पूर्णांक pmf_parser_rmw_i2c(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 maskbytes = pmf_next32(cmd);
	u32 valuesbytes = pmf_next32(cmd);
	u32 totalbytes = pmf_next32(cmd);
	स्थिर व्योम *maskblob = pmf_next_blob(cmd, maskbytes);
	स्थिर व्योम *valuesblob = pmf_next_blob(cmd, valuesbytes);

	LOG_PARSE("pmf: rmw_i2c(maskbytes: %ud, valuebytes: %ud, "
		  "totalbytes: %d) ...\n",
		  maskbytes, valuesbytes, totalbytes);
	LOG_BLOB("pmf:   mask data: \n", maskblob, maskbytes);
	LOG_BLOB("pmf:   values data: \n", valuesblob, valuesbytes);

	PMF_PARSE_CALL(rmw_i2c, cmd, h, maskbytes, valuesbytes, totalbytes,
		       maskblob, valuesblob);
पूर्ण

अटल पूर्णांक pmf_parser_पढ़ो_cfg(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 bytes = pmf_next32(cmd);

	LOG_PARSE("pmf: read_cfg(offset: %x, bytes: %ud)\n", offset, bytes);

	PMF_PARSE_CALL(पढ़ो_cfg, cmd, h, offset, bytes);
पूर्ण


अटल पूर्णांक pmf_parser_ग_लिखो_cfg(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 bytes = pmf_next32(cmd);
	स्थिर व्योम *blob = pmf_next_blob(cmd, bytes);

	LOG_PARSE("pmf: write_cfg(offset: %x, bytes: %ud)\n", offset, bytes);
	LOG_BLOB("pmf:   data: \n", blob, bytes);

	PMF_PARSE_CALL(ग_लिखो_cfg, cmd, h, offset, bytes, blob);
पूर्ण

अटल पूर्णांक pmf_parser_rmw_cfg(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 maskbytes = pmf_next32(cmd);
	u32 valuesbytes = pmf_next32(cmd);
	u32 totalbytes = pmf_next32(cmd);
	स्थिर व्योम *maskblob = pmf_next_blob(cmd, maskbytes);
	स्थिर व्योम *valuesblob = pmf_next_blob(cmd, valuesbytes);

	LOG_PARSE("pmf: rmw_cfg(maskbytes: %ud, valuebytes: %ud,"
		  " totalbytes: %d) ...\n",
		  maskbytes, valuesbytes, totalbytes);
	LOG_BLOB("pmf:   mask data: \n", maskblob, maskbytes);
	LOG_BLOB("pmf:   values data: \n", valuesblob, valuesbytes);

	PMF_PARSE_CALL(rmw_cfg, cmd, h, offset, maskbytes, valuesbytes,
		       totalbytes, maskblob, valuesblob);
पूर्ण


अटल पूर्णांक pmf_parser_पढ़ो_i2c_sub(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u8 subaddr = (u8)pmf_next32(cmd);
	u32 bytes = pmf_next32(cmd);

	LOG_PARSE("pmf: read_i2c_sub(subaddr: %x, bytes: %ud)\n",
		  subaddr, bytes);

	PMF_PARSE_CALL(पढ़ो_i2c_sub, cmd, h, subaddr, bytes);
पूर्ण

अटल पूर्णांक pmf_parser_ग_लिखो_i2c_sub(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u8 subaddr = (u8)pmf_next32(cmd);
	u32 bytes = pmf_next32(cmd);
	स्थिर व्योम *blob = pmf_next_blob(cmd, bytes);

	LOG_PARSE("pmf: write_i2c_sub(subaddr: %x, bytes: %ud) ...\n",
		  subaddr, bytes);
	LOG_BLOB("pmf:   data: \n", blob, bytes);

	PMF_PARSE_CALL(ग_लिखो_i2c_sub, cmd, h, subaddr, bytes, blob);
पूर्ण

अटल पूर्णांक pmf_parser_set_i2c_mode(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u32 mode = pmf_next32(cmd);

	LOG_PARSE("pmf: set_i2c_mode(mode: %d)\n", mode);

	PMF_PARSE_CALL(set_i2c_mode, cmd, h, mode);
पूर्ण


अटल पूर्णांक pmf_parser_rmw_i2c_sub(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h)
अणु
	u8 subaddr = (u8)pmf_next32(cmd);
	u32 maskbytes = pmf_next32(cmd);
	u32 valuesbytes = pmf_next32(cmd);
	u32 totalbytes = pmf_next32(cmd);
	स्थिर व्योम *maskblob = pmf_next_blob(cmd, maskbytes);
	स्थिर व्योम *valuesblob = pmf_next_blob(cmd, valuesbytes);

	LOG_PARSE("pmf: rmw_i2c_sub(subaddr: %x, maskbytes: %ud, valuebytes: %ud"
		  ", totalbytes: %d) ...\n",
		  subaddr, maskbytes, valuesbytes, totalbytes);
	LOG_BLOB("pmf:   mask data: \n", maskblob, maskbytes);
	LOG_BLOB("pmf:   values data: \n", valuesblob, valuesbytes);

	PMF_PARSE_CALL(rmw_i2c_sub, cmd, h, subaddr, maskbytes, valuesbytes,
		       totalbytes, maskblob, valuesblob);
पूर्ण

अटल पूर्णांक pmf_parser_पढ़ो_reg32_msrx(काष्ठा pmf_cmd *cmd,
				      काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);
	u32 shअगरt = pmf_next32(cmd);
	u32 xor = pmf_next32(cmd);

	LOG_PARSE("pmf: read_reg32_msrx(offset: %x, mask: %x, shift: %x,"
		  " xor: %x\n", offset, mask, shअगरt, xor);

	PMF_PARSE_CALL(पढ़ो_reg32_msrx, cmd, h, offset, mask, shअगरt, xor);
पूर्ण

अटल पूर्णांक pmf_parser_पढ़ो_reg16_msrx(काष्ठा pmf_cmd *cmd,
				      काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);
	u32 shअगरt = pmf_next32(cmd);
	u32 xor = pmf_next32(cmd);

	LOG_PARSE("pmf: read_reg16_msrx(offset: %x, mask: %x, shift: %x,"
		  " xor: %x\n", offset, mask, shअगरt, xor);

	PMF_PARSE_CALL(पढ़ो_reg16_msrx, cmd, h, offset, mask, shअगरt, xor);
पूर्ण
अटल पूर्णांक pmf_parser_पढ़ो_reg8_msrx(काष्ठा pmf_cmd *cmd,
				     काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);
	u32 shअगरt = pmf_next32(cmd);
	u32 xor = pmf_next32(cmd);

	LOG_PARSE("pmf: read_reg8_msrx(offset: %x, mask: %x, shift: %x,"
		  " xor: %x\n", offset, mask, shअगरt, xor);

	PMF_PARSE_CALL(पढ़ो_reg8_msrx, cmd, h, offset, mask, shअगरt, xor);
पूर्ण

अटल पूर्णांक pmf_parser_ग_लिखो_reg32_slm(काष्ठा pmf_cmd *cmd,
				      काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 shअगरt = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	LOG_PARSE("pmf: write_reg32_slm(offset: %x, shift: %x, mask: %x\n",
		  offset, shअगरt, mask);

	PMF_PARSE_CALL(ग_लिखो_reg32_slm, cmd, h, offset, shअगरt, mask);
पूर्ण

अटल पूर्णांक pmf_parser_ग_लिखो_reg16_slm(काष्ठा pmf_cmd *cmd,
				      काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 shअगरt = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	LOG_PARSE("pmf: write_reg16_slm(offset: %x, shift: %x, mask: %x\n",
		  offset, shअगरt, mask);

	PMF_PARSE_CALL(ग_लिखो_reg16_slm, cmd, h, offset, shअगरt, mask);
पूर्ण

अटल पूर्णांक pmf_parser_ग_लिखो_reg8_slm(काष्ठा pmf_cmd *cmd,
				     काष्ठा pmf_handlers *h)
अणु
	u32 offset = pmf_next32(cmd);
	u32 shअगरt = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	LOG_PARSE("pmf: write_reg8_slm(offset: %x, shift: %x, mask: %x\n",
		  offset, shअगरt, mask);

	PMF_PARSE_CALL(ग_लिखो_reg8_slm, cmd, h, offset, shअगरt, mask);
पूर्ण

अटल पूर्णांक pmf_parser_mask_and_compare(काष्ठा pmf_cmd *cmd,
				       काष्ठा pmf_handlers *h)
अणु
	u32 bytes = pmf_next32(cmd);
	स्थिर व्योम *maskblob = pmf_next_blob(cmd, bytes);
	स्थिर व्योम *valuesblob = pmf_next_blob(cmd, bytes);

	LOG_PARSE("pmf: mask_and_compare(length: %ud ...\n", bytes);
	LOG_BLOB("pmf:   mask data: \n", maskblob, bytes);
	LOG_BLOB("pmf:   values data: \n", valuesblob, bytes);

	PMF_PARSE_CALL(mask_and_compare, cmd, h,
		       bytes, maskblob, valuesblob);
पूर्ण


प्रकार पूर्णांक (*pmf_cmd_parser_t)(काष्ठा pmf_cmd *cmd, काष्ठा pmf_handlers *h);

अटल pmf_cmd_parser_t pmf_parsers[PMF_CMD_COUNT] =
अणु
	शून्य,
	pmf_parser_ग_लिखो_gpio,
	pmf_parser_पढ़ो_gpio,
	pmf_parser_ग_लिखो_reg32,
	pmf_parser_पढ़ो_reg32,
	pmf_parser_ग_लिखो_reg16,
	pmf_parser_पढ़ो_reg16,
	pmf_parser_ग_लिखो_reg8,
	pmf_parser_पढ़ो_reg8,
	pmf_parser_delay,
	pmf_parser_रुको_reg32,
	pmf_parser_रुको_reg16,
	pmf_parser_रुको_reg8,
	pmf_parser_पढ़ो_i2c,
	pmf_parser_ग_लिखो_i2c,
	pmf_parser_rmw_i2c,
	शून्य, /* Bogus command */
	शून्य, /* Shअगरt bytes right: NYI */
	शून्य, /* Shअगरt bytes left: NYI */
	pmf_parser_पढ़ो_cfg,
	pmf_parser_ग_लिखो_cfg,
	pmf_parser_rmw_cfg,
	pmf_parser_पढ़ो_i2c_sub,
	pmf_parser_ग_लिखो_i2c_sub,
	pmf_parser_set_i2c_mode,
	pmf_parser_rmw_i2c_sub,
	pmf_parser_पढ़ो_reg32_msrx,
	pmf_parser_पढ़ो_reg16_msrx,
	pmf_parser_पढ़ो_reg8_msrx,
	pmf_parser_ग_लिखो_reg32_slm,
	pmf_parser_ग_लिखो_reg16_slm,
	pmf_parser_ग_लिखो_reg8_slm,
	pmf_parser_mask_and_compare,
पूर्ण;

काष्ठा pmf_device अणु
	काष्ठा list_head	link;
	काष्ठा device_node	*node;
	काष्ठा pmf_handlers	*handlers;
	काष्ठा list_head	functions;
	काष्ठा kref		ref;
पूर्ण;

अटल LIST_HEAD(pmf_devices);
अटल DEFINE_SPINLOCK(pmf_lock);
अटल DEFINE_MUTEX(pmf_irq_mutex);

अटल व्योम pmf_release_device(काष्ठा kref *kref)
अणु
	काष्ठा pmf_device *dev = container_of(kref, काष्ठा pmf_device, ref);
	kमुक्त(dev);
पूर्ण

अटल अंतरभूत व्योम pmf_put_device(काष्ठा pmf_device *dev)
अणु
	kref_put(&dev->ref, pmf_release_device);
पूर्ण

अटल अंतरभूत काष्ठा pmf_device *pmf_get_device(काष्ठा pmf_device *dev)
अणु
	kref_get(&dev->ref);
	वापस dev;
पूर्ण

अटल अंतरभूत काष्ठा pmf_device *pmf_find_device(काष्ठा device_node *np)
अणु
	काष्ठा pmf_device *dev;

	list_क्रम_each_entry(dev, &pmf_devices, link) अणु
		अगर (dev->node == np)
			वापस pmf_get_device(dev);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक pmf_parse_one(काष्ठा pmf_function *func,
			 काष्ठा pmf_handlers *handlers,
			 व्योम *instdata, काष्ठा pmf_args *args)
अणु
	काष्ठा pmf_cmd cmd;
	u32 ccode;
	पूर्णांक count, rc;

	cmd.cmdptr		= func->data;
	cmd.cmdend		= func->data + func->length;
	cmd.func       		= func;
	cmd.instdata		= instdata;
	cmd.args		= args;
	cmd.error		= 0;

	LOG_PARSE("pmf: func %s, %d bytes, %s...\n",
		  func->name, func->length,
		  handlers ? "executing" : "parsing");

	/* One subcommand to parse क्रम now */
	count = 1;

	जबतक(count-- && cmd.cmdptr < cmd.cmdend) अणु
		/* Get opcode */
		ccode = pmf_next32(&cmd);
		/* Check अगर we are hitting a command list, fetch new count */
		अगर (ccode == 0) अणु
			count = pmf_next32(&cmd) - 1;
			ccode = pmf_next32(&cmd);
		पूर्ण
		अगर (cmd.error) अणु
			LOG_ERROR("pmf: parse error, not enough data\n");
			वापस -ENXIO;
		पूर्ण
		अगर (ccode >= PMF_CMD_COUNT) अणु
			LOG_ERROR("pmf: command code %d unknown !\n", ccode);
			वापस -ENXIO;
		पूर्ण
		अगर (pmf_parsers[ccode] == शून्य) अणु
			LOG_ERROR("pmf: no parser for command %d !\n", ccode);
			वापस -ENXIO;
		पूर्ण
		rc = pmf_parsers[ccode](&cmd, handlers);
		अगर (rc != 0) अणु
			LOG_ERROR("pmf: parser for command %d returned"
				  " error %d\n", ccode, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	/* We are करोing an initial parse pass, we need to adjust the size */
	अगर (handlers == शून्य)
		func->length = cmd.cmdptr - func->data;

	वापस 0;
पूर्ण

अटल पूर्णांक pmf_add_function_prop(काष्ठा pmf_device *dev, व्योम *driverdata,
				 स्थिर अक्षर *name, u32 *data,
				 अचिन्हित पूर्णांक length)
अणु
	पूर्णांक count = 0;
	काष्ठा pmf_function *func = शून्य;

	DBG("pmf: Adding functions for platform-do-%s\n", name);

	जबतक (length >= 12) अणु
		/* Allocate a काष्ठाure */
		func = kzalloc(माप(*func), GFP_KERNEL);
		अगर (func == शून्य)
			जाओ bail;
		kref_init(&func->ref);
		INIT_LIST_HEAD(&func->irq_clients);
		func->node = dev->node;
		func->driver_data = driverdata;
		func->name = name;
		func->phandle = data[0];
		func->flags = data[1];
		data += 2;
		length -= 8;
		func->data = data;
		func->length = length;
		func->dev = dev;
		DBG("pmf: idx %d: flags=%08x, phandle=%08x "
		    " %d bytes remaining, parsing...\n",
		    count+1, func->flags, func->phandle, length);
		अगर (pmf_parse_one(func, शून्य, शून्य, शून्य)) अणु
			kमुक्त(func);
			जाओ bail;
		पूर्ण
		length -= func->length;
		data = (u32 *)(((u8 *)data) + func->length);
		list_add(&func->link, &dev->functions);
		pmf_get_device(dev);
		count++;
	पूर्ण
 bail:
	DBG("pmf: Added %d functions\n", count);

	वापस count;
पूर्ण

अटल पूर्णांक pmf_add_functions(काष्ठा pmf_device *dev, व्योम *driverdata)
अणु
	काष्ठा property *pp;
#घोषणा PP_PREFIX "platform-do-"
	स्थिर पूर्णांक plen = म_माप(PP_PREFIX);
	पूर्णांक count = 0;

	क्रम (pp = dev->node->properties; pp != 0; pp = pp->next) अणु
		स्थिर अक्षर *name;
		अगर (म_भेदन(pp->name, PP_PREFIX, plen) != 0)
			जारी;
		name = pp->name + plen;
		अगर (म_माप(name) && pp->length >= 12)
			count += pmf_add_function_prop(dev, driverdata, name,
						       pp->value, pp->length);
	पूर्ण
	वापस count;
पूर्ण


पूर्णांक pmf_रेजिस्टर_driver(काष्ठा device_node *np,
			काष्ठा pmf_handlers *handlers,
			व्योम *driverdata)
अणु
	काष्ठा pmf_device *dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (handlers == शून्य)
		वापस -EINVAL;

	DBG("pmf: registering driver for node %pOF\n", np);

	spin_lock_irqsave(&pmf_lock, flags);
	dev = pmf_find_device(np);
	spin_unlock_irqrestore(&pmf_lock, flags);
	अगर (dev != शून्य) अणु
		DBG("pmf: already there !\n");
		pmf_put_device(dev);
		वापस -EBUSY;
	पूर्ण

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		DBG("pmf: no memory !\n");
		वापस -ENOMEM;
	पूर्ण
	kref_init(&dev->ref);
	dev->node = of_node_get(np);
	dev->handlers = handlers;
	INIT_LIST_HEAD(&dev->functions);

	rc = pmf_add_functions(dev, driverdata);
	अगर (rc == 0) अणु
		DBG("pmf: no functions, disposing.. \n");
		of_node_put(np);
		kमुक्त(dev);
		वापस -ENODEV;
	पूर्ण

	spin_lock_irqsave(&pmf_lock, flags);
	list_add(&dev->link, &pmf_devices);
	spin_unlock_irqrestore(&pmf_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmf_रेजिस्टर_driver);

काष्ठा pmf_function *pmf_get_function(काष्ठा pmf_function *func)
अणु
	अगर (!try_module_get(func->dev->handlers->owner))
		वापस शून्य;
	kref_get(&func->ref);
	वापस func;
पूर्ण
EXPORT_SYMBOL_GPL(pmf_get_function);

अटल व्योम pmf_release_function(काष्ठा kref *kref)
अणु
	काष्ठा pmf_function *func =
		container_of(kref, काष्ठा pmf_function, ref);
	pmf_put_device(func->dev);
	kमुक्त(func);
पूर्ण

अटल अंतरभूत व्योम __pmf_put_function(काष्ठा pmf_function *func)
अणु
	kref_put(&func->ref, pmf_release_function);
पूर्ण

व्योम pmf_put_function(काष्ठा pmf_function *func)
अणु
	अगर (func == शून्य)
		वापस;
	module_put(func->dev->handlers->owner);
	__pmf_put_function(func);
पूर्ण
EXPORT_SYMBOL_GPL(pmf_put_function);

व्योम pmf_unरेजिस्टर_driver(काष्ठा device_node *np)
अणु
	काष्ठा pmf_device *dev;
	अचिन्हित दीर्घ flags;

	DBG("pmf: unregistering driver for node %pOF\n", np);

	spin_lock_irqsave(&pmf_lock, flags);
	dev = pmf_find_device(np);
	अगर (dev == शून्य) अणु
		DBG("pmf: not such driver !\n");
		spin_unlock_irqrestore(&pmf_lock, flags);
		वापस;
	पूर्ण
	list_del(&dev->link);

	जबतक(!list_empty(&dev->functions)) अणु
		काष्ठा pmf_function *func =
			list_entry(dev->functions.next, typeof(*func), link);
		list_del(&func->link);
		__pmf_put_function(func);
	पूर्ण

	pmf_put_device(dev);
	spin_unlock_irqrestore(&pmf_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pmf_unरेजिस्टर_driver);

अटल काष्ठा pmf_function *__pmf_find_function(काष्ठा device_node *target,
					 स्थिर अक्षर *name, u32 flags)
अणु
	काष्ठा device_node *actor = of_node_get(target);
	काष्ठा pmf_device *dev;
	काष्ठा pmf_function *func, *result = शून्य;
	अक्षर fname[64];
	स्थिर u32 *prop;
	u32 ph;

	/*
	 * Look क्रम a "platform-*" function reference. If we can't find
	 * one, then we fallback to a direct call attempt
	 */
	snम_लिखो(fname, 63, "platform-%s", name);
	prop = of_get_property(target, fname, शून्य);
	अगर (prop == शून्य)
		जाओ find_it;
	ph = *prop;
	अगर (ph == 0)
		जाओ find_it;

	/*
	 * Ok, now try to find the actor. If we can't find it, we fail,
	 * there is no poपूर्णांक in falling back there
	 */
	of_node_put(actor);
	actor = of_find_node_by_phandle(ph);
	अगर (actor == शून्य)
		वापस शून्य;
 find_it:
	dev = pmf_find_device(actor);
	अगर (dev == शून्य) अणु
		result = शून्य;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(func, &dev->functions, link) अणु
		अगर (name && म_भेद(name, func->name))
			जारी;
		अगर (func->phandle && target->phandle != func->phandle)
			जारी;
		अगर ((func->flags & flags) == 0)
			जारी;
		result = func;
		अवरोध;
	पूर्ण
	pmf_put_device(dev);
out:
	of_node_put(actor);
	वापस result;
पूर्ण


पूर्णांक pmf_रेजिस्टर_irq_client(काष्ठा device_node *target,
			    स्थिर अक्षर *name,
			    काष्ठा pmf_irq_client *client)
अणु
	काष्ठा pmf_function *func;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pmf_lock, flags);
	func = __pmf_find_function(target, name, PMF_FLAGS_INT_GEN);
	अगर (func)
		func = pmf_get_function(func);
	spin_unlock_irqrestore(&pmf_lock, flags);
	अगर (func == शून्य)
		वापस -ENODEV;

	/* guard against manipulations of list */
	mutex_lock(&pmf_irq_mutex);
	अगर (list_empty(&func->irq_clients))
		func->dev->handlers->irq_enable(func);

	/* guard against pmf_करो_irq जबतक changing list */
	spin_lock_irqsave(&pmf_lock, flags);
	list_add(&client->link, &func->irq_clients);
	spin_unlock_irqrestore(&pmf_lock, flags);

	client->func = func;
	mutex_unlock(&pmf_irq_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmf_रेजिस्टर_irq_client);

व्योम pmf_unरेजिस्टर_irq_client(काष्ठा pmf_irq_client *client)
अणु
	काष्ठा pmf_function *func = client->func;
	अचिन्हित दीर्घ flags;

	BUG_ON(func == शून्य);

	/* guard against manipulations of list */
	mutex_lock(&pmf_irq_mutex);
	client->func = शून्य;

	/* guard against pmf_करो_irq जबतक changing list */
	spin_lock_irqsave(&pmf_lock, flags);
	list_del(&client->link);
	spin_unlock_irqrestore(&pmf_lock, flags);

	अगर (list_empty(&func->irq_clients))
		func->dev->handlers->irq_disable(func);
	mutex_unlock(&pmf_irq_mutex);
	pmf_put_function(func);
पूर्ण
EXPORT_SYMBOL_GPL(pmf_unरेजिस्टर_irq_client);


व्योम pmf_करो_irq(काष्ठा pmf_function *func)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pmf_irq_client *client;

	/* For now, using a spinlock over the whole function. Can be made
	 * to drop the lock using 2 lists अगर necessary
	 */
	spin_lock_irqsave(&pmf_lock, flags);
	list_क्रम_each_entry(client, &func->irq_clients, link) अणु
		अगर (!try_module_get(client->owner))
			जारी;
		client->handler(client->data);
		module_put(client->owner);
	पूर्ण
	spin_unlock_irqrestore(&pmf_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pmf_करो_irq);


पूर्णांक pmf_call_one(काष्ठा pmf_function *func, काष्ठा pmf_args *args)
अणु
	काष्ठा pmf_device *dev = func->dev;
	व्योम *instdata = शून्य;
	पूर्णांक rc = 0;

	DBG(" ** pmf_call_one(%pOF/%s) **\n", dev->node, func->name);

	अगर (dev->handlers->begin)
		instdata = dev->handlers->begin(func, args);
	rc = pmf_parse_one(func, dev->handlers, instdata, args);
	अगर (dev->handlers->end)
		dev->handlers->end(func, instdata);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pmf_call_one);

पूर्णांक pmf_करो_functions(काष्ठा device_node *np, स्थिर अक्षर *name,
		     u32 phandle, u32 fflags, काष्ठा pmf_args *args)
अणु
	काष्ठा pmf_device *dev;
	काष्ठा pmf_function *func, *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -ENODEV;

	spin_lock_irqsave(&pmf_lock, flags);

	dev = pmf_find_device(np);
	अगर (dev == शून्य) अणु
		spin_unlock_irqrestore(&pmf_lock, flags);
		वापस -ENODEV;
	पूर्ण
	list_क्रम_each_entry_safe(func, पंचांगp, &dev->functions, link) अणु
		अगर (name && म_भेद(name, func->name))
			जारी;
		अगर (phandle && func->phandle && phandle != func->phandle)
			जारी;
		अगर ((func->flags & fflags) == 0)
			जारी;
		अगर (pmf_get_function(func) == शून्य)
			जारी;
		spin_unlock_irqrestore(&pmf_lock, flags);
		rc = pmf_call_one(func, args);
		pmf_put_function(func);
		spin_lock_irqsave(&pmf_lock, flags);
	पूर्ण
	pmf_put_device(dev);
	spin_unlock_irqrestore(&pmf_lock, flags);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pmf_करो_functions);


काष्ठा pmf_function *pmf_find_function(काष्ठा device_node *target,
				       स्थिर अक्षर *name)
अणु
	काष्ठा pmf_function *func;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pmf_lock, flags);
	func = __pmf_find_function(target, name, PMF_FLAGS_ON_DEMAND);
	अगर (func)
		func = pmf_get_function(func);
	spin_unlock_irqrestore(&pmf_lock, flags);
	वापस func;
पूर्ण
EXPORT_SYMBOL_GPL(pmf_find_function);

पूर्णांक pmf_call_function(काष्ठा device_node *target, स्थिर अक्षर *name,
		      काष्ठा pmf_args *args)
अणु
	काष्ठा pmf_function *func = pmf_find_function(target, name);
	पूर्णांक rc;

	अगर (func == शून्य)
		वापस -ENODEV;

	rc = pmf_call_one(func, args);
	pmf_put_function(func);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pmf_call_function);

